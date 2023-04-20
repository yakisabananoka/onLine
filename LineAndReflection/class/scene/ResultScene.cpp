#include <algorithm>
#include <iomanip>
#include <sstream>
#include <DxLib.h>
#include "SceneMng.h"
#include "../common/ImageMng.h"
#include "../common/FontMng.h"
#include "../common/SoundMng.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "SceneArgsStruct.h"
#include "../UI/UIObj/NormalButton.h"
#include "../UI/UIObj/ButtonCommand/ToNextSceneBC.h"
#include "../UI/UIObj/ImagePanel.h"

namespace result_const
{
    constexpr char bgPath[] = "data/image/opt_bg.png";
    constexpr char bgmKey[] = "result";

    namespace imagePanel
    {
        constexpr char image[] = "data/image/window_frame.png";
        constexpr Vector2Dbl pos = { 512.0,384.0 };


        namespace gameclear
        {
            constexpr char image[] = "data/image/gameClear.png";
            constexpr Vector2Dbl pos = { 512.0,300.0 };
        }
    }

    namespace param
    {
        constexpr Vector2 pos = { 300,400 };

        constexpr double maxTotalLineDist = 99999.9;
        constexpr double maxCntTime=99999.9;
    }

    namespace button
    {
        constexpr char image[] = "data/image/002_05.png";
        constexpr char imageClick[] = "data/image/002_05_click.png";
        constexpr char imageHover[] = "data/image/002_05_hover.png";

        constexpr char fontKey[] = "result_button";
        constexpr char fontPath[] = "data/font/03スマートフォントUI.otf";
        constexpr char fontName[] = "03スマートフォントUI";
        constexpr int fontSize = 30;
        constexpr int fontThick = 10;

        constexpr unsigned int textColor = 0x000000;
        constexpr unsigned int edgeColor = 0xffffff;

        constexpr Vector2Dbl clickOffset = { 0.0,10.0 };
        constexpr Vector2Dbl basePos = { 512.0,570.0 };

        namespace ret
        {
            constexpr char text[] = "マップ選択に戻る";
            constexpr Vector2Dbl pos = basePos;

            constexpr char nextMap[] = "data/map/select1.json";
        }

    }
   
}

using namespace result_const;
using namespace button;

ResultScene::ResultScene(std::shared_ptr<SceneArgsStruct::ResultArgs> args):
    BaseScene(args),cntTime_(args->cntTime_),totalLineDist_(args->totalLineDist_)
{
    Init();
}

ResultScene::~ResultScene()
{
}

bool ResultScene::Init(void)
{
    lpImageMng.GetID(bgPath);
    lpSoundMng.LoadSound(bgmKey);
    controller_ = lpSceneMng.GetController();

    if (isnan(cntTime_))
    {
        cntTime_ = param::maxCntTime;
    }
    if (isnan(totalLineDist_))
    {
        totalLineDist_ = param::maxTotalLineDist;
    }

    cntTime_ = std::clamp(cntTime_, 0.0, param::maxCntTime);
    totalLineDist_ = std::clamp(totalLineDist_, 0.0, param::maxTotalLineDist);

    InitUI();
    return true;
}

uniBaseScene ResultScene::Update(double delta, uniBaseScene ownScene)
{
    uiCtrl_.Update(delta);

    DrawOwnScreen();
    return ownScene;
}

void ResultScene::DrawOwnScreen(void)
{
    SetDrawScreen(scrID_);
    ClsDrawScreen();

    DrawGraph(0, 0, lpImageMng.GetID(bgPath)[0], true);

    uiCtrl_.Draw();

    std::stringstream ss;
    ss << std::fixed;
    ss << "使用した線の量：" << std::setprecision(1) << totalLineDist_ << "mm" << std::endl << "かかった時間：" << std::setprecision(1) << cntTime_ << "秒" << std::endl;
    DrawStringToHandle(param::pos.x, param::pos.y, ss.str().c_str(), 0xffffff, lpFontMng.GetID(fontKey), 0x000000);
}

void ResultScene::InitUI(void)
{
    //事前に登録
    lpFontMng.GetID(fontKey, fontPath, fontName, fontSize, fontThick, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

    auto windowPtr = std::make_unique<ImagePanel>(Vector2Dbl(), imagePanel::image);
    windowPtr->SetCC(imagePanel::pos);

    uiCtrl_.SetUI(std::move(windowPtr));

    auto gcPtr = std::make_unique<ImagePanel>(Vector2Dbl(), imagePanel::gameclear::image);
    gcPtr->SetCC(imagePanel::gameclear::pos);

    uiCtrl_.SetUI(std::move(gcPtr));

    auto retPtr = std::make_unique<NormalButton>(
        button::ret::pos,button::ret::text, button::fontKey, button::textColor, button::edgeColor,
        button::image, button::imageHover, button::imageClick,
        std::make_unique<ToNextSceneBC>(SceneID::Game, TransitionID::FadeIO,
            std::make_shared<SceneArgsStruct::GameArgs>(button::ret::nextMap),
            std::make_shared<SceneArgsStruct::Transition::FadeIOArgs>()),
        button::clickOffset);

    uiCtrl_.SetUI(std::move(retPtr));
}

void ResultScene::PlaySceneBGM(void)
{
    lpSoundMng.PlayBGM(bgmKey);
}
