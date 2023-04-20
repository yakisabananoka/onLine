#include "CorrectLine.h"
#include "../common/Utility.h"
#include "../../_debug/_debugConOut.h"

namespace correctline_const
{
	constexpr int cntThreshold = 5;									//サンプル回数
	constexpr double thetaThreshold = DX_PI * 15.0 / 180.0;			//一つの角の閾値
	constexpr double totalThetaThreshold = DX_PI * 90.0 / 180.0;	//合計の角の閾値
	constexpr double totalDisThreshold = 30.0;						//短距離統合の閾値
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
	//時間外の場合は削除
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

	//一番最後の確定点のイテレーターを取得
	auto itr = std::find_if(nodeList_.rbegin(), nodeList_.rend(), [](Node& node) {return node.state == Node::State::COMPLETE; });
	if ((itr->pos - nodeList_.back().pos).Magnitude() < totalDisThreshold)
	{
		//終端点からの距離が近い場合は削除対象
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

	TRACE("サイズ：%zd\n", nodeList_.size());

}

void CorrectLine::EdgeCorrect(void)
{
	//座標の数が3未満の時は実行しない
	if (nodeList_.size() < 3)
	{
		return;
	}

	// 初期化
	double baseTheta = 0.0;						//基準になる角度
	double sumAngle = 0.0;						//πとの差分の総和
	double sharpAngle = 0.0;					//最も鋭い角度

	auto sharpItr = nodeList_.begin();			//最も鋭い角度のイテレーター

	auto beforeItr = nodeList_.begin();			//前のイテレーター
	auto nowItr = std::next(beforeItr, 1);		//現在のイテレーター
	auto nextItr = std::next(nowItr, 1);		//後のイテレーター

	auto preNodeItr = nodeList_.begin();		//前の完了済みノードのイテレーター
	
	int cnt = 0;								//ループ回数カウント値

	auto radIn2PI = utility::RadIn2PI();		//ラジアン値を0～2πに収める
	auto diffRad = utility::DiffRad();			//ラジアン値の差分を導出する関数オブジェクト

	for (; nextItr != nodeList_.end(); ++beforeItr, ++nowItr, ++nextItr)
	{
		//確定している場合スキップ
		if (nowItr->state == Node::State::COMPLETE)
		{
			++preNodeItr;
			continue;
		}

		//それぞれの座標位置を取得
		const auto& beforePos = beforeItr->pos;
		const auto& nowPos = nowItr->pos;
		const auto& nextPos = nextItr->pos;

		auto nbVec = beforePos - nowPos;
		auto nnVec = nextPos - nowPos;
		
		double theta = radIn2PI(atan2(nnVec.Cross(nbVec), nnVec.Dot(nbVec)));		//現在の角度
		double deltaTheta = diffRad(DX_PI, theta);									//前との角度差分

		//差分の角度の絶対値が現在のsharpAngleの絶対値より大きい場合
		//もしくは差分の角度の総和の絶対値が現在のmaxAngleの絶対値より大きい場合
		if (abs(deltaTheta) > abs(sharpAngle))
		//if (deltaTheta* deltaTheta > sharpAngle* sharpAngle)
		{
			sharpItr = nowItr;
			sharpAngle = deltaTheta;
		}

		//総和に対して加算
		sumAngle += deltaTheta;

		//カウント値を加算
		cnt++;

		//TRACE("posX:%f,posY:%f,theta:%f,deltaTheta:%f,sharpAnlge:%f,sumAngle:%f\n", nowPos.x, nowPos.y, theta, deltaTheta, (sharpAngle), ((sumAngle)));

		//ループ回数が閾値以上の場合
		if (cnt > cntThreshold)
		{
			//thetaかmaxAngleが閾値以上の場合
			if (abs(sharpAngle) > thetaThreshold || (abs((sumAngle)) > totalThetaThreshold))
			{
				//ノード位置を確定
				sharpItr->state = Node::State::COMPLETE;
				sharpItr->dist = (sharpItr->pos - preNodeItr->pos).Magnitude();

				//角度リセット
				sumAngle = 0.0;
				sharpAngle = 0.0;
				cnt = 0;

			}
		}

	}

	//確定済みノードの総距離チェック
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
