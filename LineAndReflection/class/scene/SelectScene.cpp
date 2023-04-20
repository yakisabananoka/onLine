#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../common/FontMng.h"
#include "../UI/UIObj/Button.h"
#include "../UI/UIObj/ButtonCommand/ButtonCommandFunc.h"
#include "../UI/UIObj/ButtonCommand/ToNextSceneBC.h"
#include "../UI/Panels.h"
#include "../scene/SceneArgsStruct.h"
#include "SelectScene.h"

namespace select_cosnt
{
    constexpr char bgPath[] = "data/image/select_bg.png";

    namespace button
    {
        constexpr char image[] = "data/image/002_05.png";
        constexpr char imageClick[] = "data/image/002_05_click.png";
        constexpr char imageHover[] = "data/image/002_05_hover.png";

        constexpr char fontKey[] = "select_button";
        constexpr char fontPath[] = "data/font/03スマートフォントUI.otf";
        constexpr char fontName[] = "03スマートフォントUI";
        constexpr int fontSize = 30;
        constexpr int fontThick = 10;

        constexpr unsigned int textColor = 0x000000;
        constexpr unsigned int edgeColor = 0xffffff;

        constexpr Vector2Dbl textOffset = { 0.0,10.0 };

        constexpr char startText[] = "ステージ１";
        constexpr Vector2Dbl startPos = { 512.0,470.0 };

        constexpr Vector2Dbl interval = { 320.0,120.0 };
    }
}

using namespace select_cosnt;
using namespace button;

SelectScene::SelectScene(std::shared_ptr<SceneArgsStruct::SelectArgs> args) :
    BaseScene(args)
{
    lpImageMng.GetID(bgPath);
    Init();
    InitUI();
}

SelectScene::~SelectScene()
{
}

bool SelectScene::Init(void)
{
    return true;
}

bool SelectScene::InitUI(void)
{
    //事前に登録
    lpImageMng.GetID(image);
    lpImageMng.GetID(imageClick);
    lpImageMng.GetID(imageHover);
    lpFontMng.GetID(fontKey, fontPath, fontName, fontSize, fontThick, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

    //テスト
    for (double y = -1.0; y < 2.0; y++)
    {
        for (double x = -1.0; x < 2.0; x++)
        {
            auto startPtr = std::make_unique<Button>(Vector2Dbl(), TextOnGraphPanel()(startText, image, fontKey, textColor, edgeColor));
            startPtr->SetCC(startPos + interval * Vector2Dbl(x, y));
            startPtr->SetCommand(
                Button::State::NowEnter,
                std::make_unique<ButtonCommandFunc>([&](Button& button) { button.SetImageKey(TextOnGraphPanel()(startText, imageHover, fontKey, textColor, edgeColor)); })
            );
            startPtr->SetCommand(
                Button::State::NowLeave,
                std::make_unique<ButtonCommandFunc>([&](Button& button) { button.SetImageKey(TextOnGraphPanel()(startText, image, fontKey, textColor, edgeColor)); })
            );
            //startPtr->SetCommand(
            //    Button::State::JustOff,
            //    std::make_unique<ToNextSceneBC>(SceneID::Game, TransitionID::FadeM, std::make_shared<SceneArgsStruct::GameArgs>("data/map/tutorial1.json"))
            //);
            //startPtr->SetFunc(Button::State::JustOff, [&](Button&) {nextScene_=std::make_unique<GameScene>(std::make_shared<SceneArgsStruct::GameArgs>("data/map/map1.json")); });
            startPtr->SetCommand(
                Button::State::NowOn,
                std::make_unique<ButtonCommandFunc>([&](Button& button) { button.SetImageKey(TextOnGraphPanel()(startText, imageClick, fontKey, textColor, edgeColor, textOffset)); })
            );
            uiCtrl_.SetUI(std::move(startPtr));
        }
    }
    return true;
}

uniBaseScene SelectScene::Update(double delta, uniBaseScene ownScene)
{
    uiCtrl_.Update(delta);

    DrawOwnScreen();
    return ownScene;
}

void SelectScene::DrawOwnScreen(void)
{
    SetDrawScreen(scrID_);
    ClsDrawScreen();

    DrawGraph(0, 0, lpImageMng.GetID(bgPath)[0], true);

    uiCtrl_.Draw();
}
