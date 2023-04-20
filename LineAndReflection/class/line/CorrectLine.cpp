#include "CorrectLine.h"
#include "../common/Utility.h"
#include "../../_debug/_debugConOut.h"

namespace correctline_const
{
	constexpr int cntThreshold = 5;									//�T���v����
	constexpr double thetaThreshold = DX_PI * 15.0 / 180.0;			//��̊p��臒l
	constexpr double totalThetaThreshold = DX_PI * 90.0 / 180.0;	//���v�̊p��臒l
	constexpr double totalDisThreshold = 30.0;						//�Z����������臒l
}

using namespace correctline_const;


CorrectLine::CorrectLine(std::weak_ptr<Camera> camera, unsigned int color) :
	BaseLine(camera, color)
{
}

CorrectLine::~CorrectLine()
{
}

void CorrectLine::Update(double delta)
{
	colObjInfoVec_.clear();
	//���ԊO�̏ꍇ�͍폜
	if (time_ > GetMaxActiveTime())
	{
		state_ = State::DIE;
	}

	EdgeCorrect();

	if (state_ == State::DRAWING)
	{
		//SetPolygon(static_cast<float>(std::clamp(GetTotalLength() / GetMaxLength(), 0.0, 1.0)));
		SetPolygonAll();
	}
	else
	{
		activeTime_ += delta;
	}

	time_ += delta;
}

void CorrectLine::SetPoint(Vector2Dbl pos)
{
	if (!CheckSetPoint(pos))
	{
		return;
	}

	auto& node = nodeList_.emplace_back(pos, Node::State::INCOMPLETE, 0.0);

	if (nodeList_.size() == 1)
	{
		nodeList_.begin()->state = Node::State::COMPLETE;
		return;
	}

	node.dist = (node.pos - std::next(nodeList_.rbegin(), 1)->pos).Magnitude();
}

void CorrectLine::EndDrawingLine(void)
{
	if (state_ != State::DRAWING)
	{
		return;
	}

	//��ԍŌ�̊m��_�̃C�e���[�^�[���擾
	auto itr = std::find_if(nodeList_.rbegin(), nodeList_.rend(), [](Node& node) {return node.state == Node::State::COMPLETE; });
	if ((itr->pos - nodeList_.back().pos).Magnitude() < totalDisThreshold)
	{
		//�I�[�_����̋������߂��ꍇ�͍폜�Ώ�
		itr->state = Node::State::DISPOSAL;
	}

	nodeList_.back().state = Node::State::COMPLETE;
	nodeList_.remove_if([](Node& node) {return node.state != Node::State::COMPLETE; });

	state_ = State::STANDBY;

	if (nodeList_.size() == 1)
	{
		state_ = State::DIE;
	}

	SetPolygonAll();

	TRACE("�T�C�Y�F%zd\n", nodeList_.size());

}

void CorrectLine::EdgeCorrect(void)
{
	//���W�̐���3�����̎��͎��s���Ȃ�
	if (nodeList_.size() < 3)
	{
		return;
	}

	// ������
	double baseTheta = 0.0;						//��ɂȂ�p�x
	double sumAngle = 0.0;						//�΂Ƃ̍����̑��a
	double sharpAngle = 0.0;					//�ł��s���p�x

	auto sharpItr = nodeList_.begin();			//�ł��s���p�x�̃C�e���[�^�[

	auto beforeItr = nodeList_.begin();			//�O�̃C�e���[�^�[
	auto nowItr = std::next(beforeItr, 1);		//���݂̃C�e���[�^�[
	auto nextItr = std::next(nowItr, 1);		//��̃C�e���[�^�[

	auto preNodeItr = nodeList_.begin();		//�O�̊����ς݃m�[�h�̃C�e���[�^�[
	
	int cnt = 0;								//���[�v�񐔃J�E���g�l

	auto radIn2PI = utility::RadIn2PI();		//���W�A���l��0�`2�΂Ɏ��߂�
	auto diffRad = utility::DiffRad();			//���W�A���l�̍����𓱏o����֐��I�u�W�F�N�g

	for (; nextItr != nodeList_.end(); ++beforeItr, ++nowItr, ++nextItr)
	{
		//�m�肵�Ă���ꍇ�X�L�b�v
		if (nowItr->state == Node::State::COMPLETE)
		{
			++preNodeItr;
			continue;
		}

		//���ꂼ��̍��W�ʒu���擾
		const auto& beforePos = beforeItr->pos;
		const auto& nowPos = nowItr->pos;
		const auto& nextPos = nextItr->pos;

		auto nbVec = beforePos - nowPos;
		auto nnVec = nextPos - nowPos;
		
		double theta = radIn2PI(atan2(nnVec.Cross(nbVec), nnVec.Dot(nbVec)));		//���݂̊p�x
		double deltaTheta = diffRad(DX_PI, theta);									//�O�Ƃ̊p�x����

		//�����̊p�x�̐�Βl�����݂�sharpAngle�̐�Βl���傫���ꍇ
		//�������͍����̊p�x�̑��a�̐�Βl�����݂�maxAngle�̐�Βl���傫���ꍇ
		if (abs(deltaTheta) > abs(sharpAngle))
		//if (deltaTheta* deltaTheta > sharpAngle* sharpAngle)
		{
			sharpItr = nowItr;
			sharpAngle = deltaTheta;
		}

		//���a�ɑ΂��ĉ��Z
		sumAngle += deltaTheta;

		//�J�E���g�l�����Z
		cnt++;

		//TRACE("posX:%f,posY:%f,theta:%f,deltaTheta:%f,sharpAnlge:%f,sumAngle:%f\n", nowPos.x, nowPos.y, theta, deltaTheta, (sharpAngle), ((sumAngle)));

		//���[�v�񐔂�臒l�ȏ�̏ꍇ
		if (cnt > cntThreshold)
		{
			//theta��maxAngle��臒l�ȏ�̏ꍇ
			if (abs(sharpAngle) > thetaThreshold || (abs((sumAngle)) > totalThetaThreshold))
			{
				//�m�[�h�ʒu���m��
				sharpItr->state = Node::State::COMPLETE;
				sharpItr->dist = (sharpItr->pos - preNodeItr->pos).Magnitude();

				//�p�x���Z�b�g
				sumAngle = 0.0;
				sharpAngle = 0.0;
				cnt = 0;

			}
		}

	}

	//�m��ς݃m�[�h�̑������`�F�b�N
	if (std::count_if(nodeList_.begin(), nodeList_.end(), [](Node& node) {return node.state == Node::State::COMPLETE; }) < 3)
	{
		return;
	}

	nowItr = nodeList_.begin();
	nextItr = std::find_if(std::next(nowItr, 1), nodeList_.end(), [](Node& node) {return node.state == Node::State::COMPLETE; });

	while (nextItr != nodeList_.end())
	{
		if ((nextItr->pos - nowItr->pos).Magnitude() < totalDisThreshold)
		{
			nextItr->state = Node::State::DISPOSAL;
		}
		else
		{
			nowItr = nextItr;
		}

		nextItr = std::find_if(std::next(nowItr, 1), nodeList_.end(), [](Node& node) {return node.state == Node::State::COMPLETE; });
	}

	auto lastCompItr = std::find_if(nodeList_.rbegin(), nodeList_.rend(), [](Node& node) {return node.state == Node::State::COMPLETE; });
	for (auto itr = lastCompItr; itr != nodeList_.rend(); ++itr)
	{
		itr->state = itr->state == Node::State::COMPLETE ? Node::State::COMPLETE : Node::State::DISPOSAL;
	}

	nodeList_.remove_if([](Node& node) {return node.state == Node::State::DISPOSAL; });
}
