#include <array>
#include <DxLib.h>
#include "BaseLine.h"
#include "../scene/SceneMng.h"
#include "../common/ImageMng.h"
#include "../scene/Camera.h"
#include "../common/Utility.h"
#include "../../_debug/_debugConOut.h"
#include "../../_debug/_debugDispOut.h"

namespace baseline_const
{
	constexpr double radius = 15.0;									//���̑���
	constexpr double colRadius = 11.0;								//�����蔻��̐��̑���
	constexpr double maxActiveTime = 5.0;							//���̐�������
	constexpr double maxLength = 1500.0;							//�ő�̒���
	
	namespace image
	{
		constexpr char seImagePath[] = "data/image/Particle02.png";
		constexpr double spRate = 0.5;

		constexpr Vector2Dbl size = { 2000.0,radius * 2.0 };

		namespace milky
		{
			constexpr char path[] = "data/image/milky.png";			//���n�̉摜�̃p�X
			constexpr double speed = 20.0;
		}

		namespace star
		{
			constexpr Vector2 num = { 1,60 };

			constexpr double animSpeed = 60.0;

			namespace Low
			{
				constexpr char key[] = "data/image/starWayLow.png";
				constexpr double speed = 40.0;
			}

			namespace High
			{
				constexpr char key[] = "data/image/starWayHigh.png";
				constexpr double speed = 100.0;
			}
		}
		
	}

	namespace screen
	{
		constexpr char key[] = "lineScreen";						//���p�̃X�N���[���o�b�t�@
		constexpr Vector2Dbl size = image::size;
	}
}

using namespace baseline_const;

BaseLine::BaseLine(std::weak_ptr<Camera> camera, unsigned int color) :
	camera_(camera)
{
	time_ = 0.0;
	activeTime_ = 0.0;

	state_ = State::DRAWING;
	vertexVec_.reserve(USHRT_MAX);
	bufferVertexVec_.reserve(USHRT_MAX);
	index_.reserve(USHRT_MAX * 3);

	starWayTime_ = 0.0;
	starWayCnt_ = static_cast<double>(image::star::num.Area());

	GetColor2(color, &lineR_, &lineG_, &lineB_);
}

BaseLine::~BaseLine()
{
	//StopEffekseer2DEffect(lpEffectMng.GetID(effect::path));
}

void BaseLine::Draw(void)
{
	if ((maxActiveTime - time_) < 2.0)
	{
		if (static_cast<int>(time_ / 0.1) % 2)
		{
			return;
		}
	}

	Vector2Dbl camOffset;
	if (!camera_.expired())
	{
		camOffset = camera_.lock()->GetDrawOffset();
	}

	DrawLineScreen();
	DrawLinePolygon(camOffset);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	const auto& startPos = std::find_if(nodeList_.begin(), nodeList_.end(), [](const Node& node) {return node.state == Node::State::COMPLETE; })->pos;
	DrawRotaGraph(
		static_cast<int>(camOffset.x + startPos.x),
		static_cast<int>(camOffset.y + startPos.y),
		image::spRate, 0.0, lpImageMng.GetID(image::seImagePath)[0], true
	);

	const auto& endPos = std::find_if(nodeList_.rbegin(), nodeList_.rend(), [](const Node& node) {return node.state == Node::State::COMPLETE; })->pos;
	DrawRotaGraph(
		static_cast<int>(camOffset.x + endPos.x),
		static_cast<int>(camOffset.y + endPos.y),
		image::spRate, 0.0, lpImageMng.GetID(image::seImagePath)[0], true
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);


}

void BaseLine::ClearPoint(void)
{
	nodeList_.clear();
}

bool BaseLine::IsActive(void)
{
	return state_ != State::DIE;
}

void BaseLine::SetActive(bool flg)
{
	state_ = flg ? state_ : State::DIE;
}

const double& BaseLine::GetColRadius(void) const
{
	return colRadius;
}

bool BaseLine::IsOverLength(void) const
{
	return GetTotalLength() >= maxLength;
}

void BaseLine::PreLoadLineScreen(void)
{
	//�X�N���[���̓o�^
	if (!lpImageMng.ExistID(screen::key))
	{
		lpImageMng.GetID(screen::key, MakeScreen(static_cast<int>(screen::size.x), static_cast<int>(screen::size.y), true));
	}

	lpImageMng.GetID(
		image::star::High::key, image::star::High::key,
		static_cast<Vector2>(image::size), image::star::num);

	lpImageMng.GetID(
		image::star::Low::key, image::star::Low::key,
		static_cast<Vector2>(image::size), image::star::num);
}

void BaseLine::SetColObjInfo(ColInfoPtr ptr)
{
	colObjInfoVec_.emplace_back(std::move(ptr));
}

size_t BaseLine::CountCompNode(void)const
{
	return std::count_if(nodeList_.begin(), nodeList_.end(), [](const Node& node) {return node.state == Node::State::COMPLETE; });
}

bool BaseLine::HasCollision(void)
{
	return true;
}

double BaseLine::GetTotalLength(void)const
{
	double ret = 0.0;
	for (const auto& node : nodeList_)
	{
		if (node.state != Node::State::COMPLETE)
		{
			continue;
		}

		ret += node.dist;
	}

	if (nodeList_.back().state != Node::State::COMPLETE)
	{
		auto itr = std::find_if(nodeList_.rbegin(), nodeList_.rend(), [](const Node& node) {return node.state == Node::State::COMPLETE; });
		ret += (itr->pos - nodeList_.back().pos).Magnitude();
	}

	return ret;
}

double BaseLine::GetMaxLength(void) const
{
	return maxLength;
}

double BaseLine::GetMaxActiveTime(void)
{
	return maxActiveTime;
}

void BaseLine::SetPolygon(float maxU)
{
	size_t cntCmp = CountCompNode();

	//�m�[�h����̏ꍇ�͒��_�𑫂��Ȃ�
	if (!cntCmp)
	{
		return;
	}

	//���_�̍쐬
	auto SetVertex = [](const Vector2Dbl& nodePos, Vector2Dbl vec,float u,float v) {
		Vector2Flt pos = static_cast<Vector2Flt>(nodePos + vec);
		VERTEX2D ret;

		ret.pos = { pos.x,pos.y,0.0 };
		ret.rhw = 1.0f;
		ret.dif = GetColorU8(255, 255, 255, 255);
		ret.u = u;
		ret.v = v;

		return ret;
	};

	//�Ō�̊m��m�[�h���擾
	auto nowItr = std::find_if(nodeList_.rbegin(), nodeList_.rend(), [](const Node& node) {return node.state == Node::State::COMPLETE; });
	const auto& nowPos = nowItr->pos;

	//��������Ȃ��ꍇ���_��2����
	bool sumFlg = cntCmp * 2 != vertexVec_.size();
	if (sumFlg)
	{
		const auto& backPos = nodeList_.back().pos;

		vertexVec_.emplace_back(SetVertex(backPos, Vector2Dbl(0.0, -1.0) * radius, maxU, 0.0f));
		vertexVec_.emplace_back(SetVertex(backPos, Vector2Dbl(0.0, 1.0) * radius, maxU, 1.0f));
	}

	//�m�[�h��1�̏ꍇ�A�������I������
	if (cntCmp == 1)
	{
		return;
	}

	//�m�[�h��1�ł͂Ȃ��ꍇ�A�Ō�̓_�̈ʒu�������s��
	auto preItr = std::find_if(nowItr, nodeList_.rend(), [](const Node& node) {return node.state == Node::State::COMPLETE; });
	const auto& prePos = preItr->pos;
	auto lastRightVec = (prePos - nowPos).RotaVecRight90().Normalized() * radius;
	auto lastLeftVec = (prePos - nowPos).RotaVecLeft90().Normalized() * radius;

	auto lastRightPos = static_cast<Vector2Flt>(nowPos + lastRightVec);
	auto lastLeftPos = static_cast<Vector2Flt>(nowPos + lastLeftVec);

	vertexVec_[vertexVec_.size() - 2].pos = { lastRightPos.x,lastRightPos.y,0.0f };
	vertexVec_[vertexVec_.size() - 1].pos = { lastLeftPos.x,lastLeftPos.y,0.0f };

	//�C���f�b�N�X�f�[�^�̐ݒ�
	if (sumFlg)
	{
		int indexBase = index_.empty() ? 0 : static_cast<int>(index_.back());
		index_.emplace_back(indexBase + 0);
		index_.emplace_back(indexBase + 2);
		index_.emplace_back(indexBase + 1);
		index_.emplace_back(indexBase + 3);
		index_.emplace_back(indexBase + 1);
		index_.emplace_back(indexBase + 2);
	}
	
	//�m�[�h��2�̏ꍇ�A�ŏ��̓_�̈ʒu�������s��
	if (cntCmp == 2)
	{
		auto firstRightPos = static_cast<Vector2Flt>(prePos + lastRightVec);
		auto firstLeftPos = static_cast<Vector2Flt>(prePos + lastLeftVec);

		vertexVec_[0].pos = { firstRightPos.x,firstRightPos.y,0.0f };
		vertexVec_[1].pos = { firstLeftPos.x,firstLeftPos.y,0.0f };

		return;
	}
	
	//�Ōォ���O�̓_�̈ʒu����
	auto pre2Itr = std::find_if(preItr, nodeList_.rend(), [](const Node& node) {return node.state == Node::State::COMPLETE; });
	const auto& pre2Pos = pre2Itr->pos;

	auto preRightVec = (pre2Pos - prePos).RotaVecRight90().Normalized() * radius;
	auto preLeftVec = (pre2Pos - prePos).RotaVecLeft90().Normalized() * radius;

	auto preRightPos = static_cast<Vector2Flt>(prePos + (lastRightVec + preRightVec).Normalized() * radius);
	auto preLeftPos = static_cast<Vector2Flt>(prePos + (lastLeftVec + preLeftVec).Normalized() * radius);

	vertexVec_[vertexVec_.size() - 3].pos = { preRightPos.x,preRightPos.y,0.0f };
	vertexVec_[vertexVec_.size() - 4].pos = { preLeftPos.x,preLeftPos.y,0.0f };
	
}

void BaseLine::SetPolygonAll(void)
{
	//�m��ς݃m�[�h��
	auto cntComp = CountCompNode();

	//�m��ς݃m�[�h��2�ɖ����Ȃ��ꍇ�͑�����s��Ȃ�
	if (cntComp < 2)
	{
		return;
	}

	//�m��m�[�h�̔���p
	auto findComp = [](const Node& node) {return node.state == Node::State::COMPLETE; };

	//���_�̍쐬
	auto setVertex = [](const Vector2Dbl& nodePos, Vector2Dbl vec, float u, float v, COLOR_U8 dif = GetColorU8(255, 255, 255, 255)) {
		Vector2Flt pos = static_cast<Vector2Flt>(nodePos + vec);
		VERTEX2D ret;

		ret.pos = { pos.x,pos.y,0.0 };
		ret.rhw = 1.0f;
		ret.dif = dif;
		ret.u = u;
		ret.v = v;

		return ret;
	};

	//UV�l�p�Ɋۂ߂�
	auto clampUV = [](double value) {
		return static_cast<float>(std::clamp(value, 0.0, 1.0));
	};

	//���_�f�[�^�̔z����폜
	vertexVec_.clear();

	//�C���f�b�N�X�f�[�^�̍폜
	index_.clear();
	
	//�O�̃C�e���[�^�[
	auto preItr = std::find_if(nodeList_.begin(), nodeList_.end(), findComp);

	//���݂̃C�e���[�^�[
	auto nowItr = std::find_if(preItr, nodeList_.end(), findComp);

	//���݂���O�̃x�N�g��
	auto vec = nowItr->pos - preItr->pos;

	//���݂���O�̃x�N�g���̍�����
	auto leftVec = vec.RotaVecLeft90();

	//���݂���O�̃x�N�g���̉E����
	auto rightVec = vec.RotaVecRight90();

	//�m��ς݃m�[�h�̐������ۏ؂���Ă��邽�ߍŏ��̈��o�^
	vertexVec_.emplace_back(setVertex(preItr->pos, leftVec.Normalized() * radius, 0.0f, 0.0f));
	vertexVec_.emplace_back(setVertex(preItr->pos, rightVec.Normalized() * radius, 0.0f, 1.0f));

	//���̃C�e���[�^�[
	auto nextItr = std::find_if(std::next(nowItr, 1), nodeList_.end(), findComp);

	//������
	auto length = vec.Magnitude();

	//U�l
	auto u = 0.0f;

	//���̃x�N�g��
	Vector2Dbl nextVec;

	//���̍������x�N�g��
	Vector2Dbl nextLeftVec;

	//���̉E�����x�N�g��
	Vector2Dbl nextRightVec;

	//�C���f�b�N�X�f�[�^�̃J�E���g�l
	int indexBase = 0;

	//�m�[�h���s����܂Ń��[�v
	while (nextItr != nodeList_.end())
	{
		//���̃x�N�g���̍X�V
		nextVec = nextItr->pos - nowItr->pos;
		nextLeftVec = nextVec.RotaVecLeft90();
		nextRightVec = nextVec.RotaVecRight90();

		//�������̍X�V
		length += vec.Magnitude();
		u = clampUV(length / image::size.x);

		//�x�N�g���ƃm�[�h�����ɓo�^
		vertexVec_.emplace_back(setVertex(nowItr->pos, (leftVec + nextLeftVec).Normalized() * radius, u, 0.0f));
		vertexVec_.emplace_back(setVertex(nowItr->pos, (rightVec + nextRightVec).Normalized() * radius, u, 1.0f));

		//�C���f�b�N�X�f�[�^�̓o�^
		index_.emplace_back(indexBase + 0);
		index_.emplace_back(indexBase + 2);
		index_.emplace_back(indexBase + 1);
		index_.emplace_back(indexBase + 3);
		index_.emplace_back(indexBase + 1);
		index_.emplace_back(indexBase + 2);
		indexBase = indexBase + 2;

		//���݂̃x�N�g���̍X�V
		vec = nextVec;
		leftVec = nextLeftVec;
		rightVec = nextRightVec;

		//�C�e���[�^�[���X�V
		preItr = nowItr;
		nowItr = nextItr;
		nextItr = std::find_if(std::next(nowItr, 1), nodeList_.end(), findComp);
	}

	//�Ō�̊m��ς݃m�[�h��o�^
	length += vec.Magnitude();
	u = clampUV(length / image::size.x);
	vertexVec_.emplace_back(setVertex(nowItr->pos, leftVec.Normalized()* radius, u, 0.0f));
	vertexVec_.emplace_back(setVertex(nowItr->pos, rightVec.Normalized()* radius, u, 1.0f));

	//�C���f�b�N�X�f�[�^�̓o�^
	index_.emplace_back(indexBase + 0);
	index_.emplace_back(indexBase + 2);
	index_.emplace_back(indexBase + 1);
	index_.emplace_back(indexBase + 3);
	index_.emplace_back(indexBase + 1);
	index_.emplace_back(indexBase + 2);

}

void BaseLine::UpdateLineScreen(double delta)
{
	milkyPos_.x = fmod(milkyPos_.x + image::milky::speed * delta, image::size.x);

	starWayHighPos_.x = fmod(starWayHighPos_.x + image::star::High::speed * delta, image::size.x);
	starWayLowPos_.x = fmod(starWayLowPos_.x + image::star::Low::speed * delta, image::size.x);

	constexpr double starNumDbl = static_cast<double>(image::star::num.Area());

	starWayTime_ += image::star::animSpeed * delta;

	double nowTime = fmod(starWayTime_, starNumDbl * 2.0);
	starWayCnt_ = -abs(-nowTime + starNumDbl) + starNumDbl;

}

bool BaseLine::CheckSetPoint(const Vector2Dbl& setPos)const
{
	//�m�[�h����̎������������W�������Ƃ�
	if (!nodeList_.empty() && nodeList_.back().pos == setPos)
	{
		return false;
	}

	//�`��r���łȂ��Ƃ�
	if (state_ != State::DRAWING)
	{
		return false;
	}

	return true;
}

void BaseLine::DrawLinePolygon(const Vector2Dbl& camOffset)
{

	Vector2Flt camOffsetFlt = static_cast<Vector2Flt>(camOffset);
	bufferVertexVec_.clear();
	bufferVertexVec_ = vertexVec_;

	for (auto& buffer : bufferVertexVec_)
	{
		buffer.pos.x += camOffsetFlt.x;
		buffer.pos.y += camOffsetFlt.y;
	}

	int polygonNum = static_cast<int>(index_.size() / 3);
	if (polygonNum)
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		DrawPolygonIndexed2D(
			bufferVertexVec_.data(), static_cast<int>(bufferVertexVec_.size()),
			index_.data(), polygonNum,
			lpImageMng.GetID(screen::key)[0], true
		);
		//DrawPolygonIndexed2D(
		//	bufferVertexVec_.data(), static_cast<int>(bufferVertexVec_.size()),
		//	index_.data(), polygonNum,
		//	DX_NONE_GRAPH, true);
		//TRACE("�`�挋�ʁF%d\n", result);
		TRACE("���_���F%zu�A�m�[�h���F%zu�A�|���S�����F%d�A\n", bufferVertexVec_.size(), nodeList_.size(), polygonNum);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

	for (const auto& vertex : bufferVertexVec_)
	{
		_dbgDrawCircle(static_cast<int>(vertex.pos.x), static_cast<int>(vertex.pos.y), 2, 0xff0000, true);
	}
}

void BaseLine::DrawLineScreen(void)
{
	int scr = GetDrawScreen();

	SetDrawScreen(lpImageMng.GetID(screen::key)[0]);
	ClsDrawScreen();

	int r = 0, g = 0, b = 0;
	GetDrawBright(&r, &g, &b);
	SetDrawBright(lineR_, lineG_, lineB_);
	//SetDrawBright(0, 0, 0);

	DrawGraph(static_cast<int>(milkyPos_.x), static_cast<int>(milkyPos_.y), lpImageMng.GetID(image::milky::path)[0], true);
	DrawGraph(static_cast<int>(milkyPos_.x - image::size.x), static_cast<int>(milkyPos_.y), lpImageMng.GetID(image::milky::path)[0], true);

	SetDrawBright(r, g, b);

	int cnt = std::clamp(static_cast<int>(starWayCnt_), 0, image::star::num.Area() - 1);

	TRACE("�A�j���[�V�����J�E���g:%d\n", cnt);

	DrawGraph(
		static_cast<int>(starWayHighPos_.x), static_cast<int>(starWayHighPos_.y),
		lpImageMng.GetID(image::star::High::key)[cnt], true
	);
	DrawGraph(
		static_cast<int>(starWayHighPos_.x - image::size.x), static_cast<int>(starWayHighPos_.y),
		lpImageMng.GetID(image::star::High::key)[cnt], true
	);
	DrawGraph(
		static_cast<int>(starWayLowPos_.x), static_cast<int>(starWayLowPos_.y),
		lpImageMng.GetID(image::star::Low::key)[cnt], true
	);
	DrawGraph( 
		static_cast<int>(starWayLowPos_.x - image::size.x), static_cast<int>(starWayLowPos_.y),
		lpImageMng.GetID(image::star::Low::key)[cnt], true
	);

	SetDrawScreen(scr);
}
