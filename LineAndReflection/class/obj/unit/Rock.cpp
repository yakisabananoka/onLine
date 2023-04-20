#include <random>
#include <DxLib.h>
#include "../../common/ImageMng.h"
#include "../../common/SoundMng.h"
#include "../../scene/Camera.h"
#include "Rock.h"

namespace rock_const
{
    constexpr char key[] = "tileset1";
    constexpr int imageId = 830;
    constexpr double size = 32.0;
    constexpr double gravity = 500.0;
    constexpr double maxSpeed = 600.0;
    constexpr Vector2Dbl rotaSpeedDist = Vector2Dbl(-1.0, 1.0) * DX_PI / 2.0;
    
    namespace explosion
    {
        constexpr char path[] = "data/image/explosion.png";
        constexpr char key[] = "explosion";
        constexpr Vector2 divCnt = Vector2(12, 1);
        constexpr Vector2Dbl divSize = Vector2Dbl(128.0, 128.0);
        constexpr double time = 0.1;
        constexpr char sound[] = "explosion";
    }
}

using namespace rock_const;

Rock::Rock(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id) :
    Enemy(camera, pos, size, id, gravity, maxSpeed)
{
    lpImageMng.GetID(explosion::path, explosion::key, explosion::divSize, explosion::divCnt);
    lpSoundMng.LoadSound(explosion::sound);
    std::random_device seed;
    std::mt19937 randomGen(seed());
    std::uniform_real_distribution<> dist(rotaSpeedDist.x, rotaSpeedDist.y);
    rotaSpeed_ = dist(randomGen);
    rotaAngle_ = 0.0;
    expId_ = 0;
}

Rock::~Rock()
{
}

void Rock::Draw(void)
{
    Vector2Dbl camOffset;
    if (!camera_.expired())
    {
        camOffset = camera_.lock()->GetDrawOffset();
    }

    Vector2 drawPos = static_cast<Vector2>(camOffset + pos_);
    if (state_ == State::Death)
    {
        DrawRotaGraph(drawPos.x, drawPos.y, 1.0, 0.0, lpImageMng.GetID(explosion::key)[expId_], true);
        return;
    }

    DrawRotaGraph(drawPos.x, drawPos.y, 1.0, rotaAngle_, lpImageMng.GetID(key)[imageId], true);
}

bool Rock::EnemyMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
    if (state_ != State::InAir)
    {
        SetState(State::Death);
        lpSoundMng.PlaySE(explosion::sound);
    }

    rotaAngle_ = rotaSpeed_ * delta;
    return false;
}

void Rock::ColMotion(double delta, ObjPtr& colObj)
{
    SetState(State::Death);
    lpSoundMng.PlaySE(explosion::sound);
}

bool Rock::DeathMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
    moveVec_ = {};
    auto cnt = static_cast<int>(stateTime_ / explosion::time);
    if (cnt >= explosion::divCnt.Area())
    {
        activeFlg_ = false;
        return true;
    }

    expId_ = cnt;

    return true;
}
