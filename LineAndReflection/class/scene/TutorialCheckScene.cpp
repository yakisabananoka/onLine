#include <DxLib.h>
#include "../common/FontMng.h"
#include "TutorialCheckScene.h"
#include "SceneArgsStruct.h"
#include "../UI/UIObj/NormalButton.h"
#include "../UI/UIObj/ImagePanel.h"
#include "../UI/Panels.h"
#include "../UI/UIObj/ButtonCommand/ToNextSceneBC.h"

namespace tutoCheck_const
{
    namespace imagePanel
    {
        constexpr char image[] = "data/image/window_frame.png";
        constexpr Vector2Dbl pos = { 512.0,384.0 };

        constexpr char text[] = "チュートリアルを行いますか？";
    }

    namespace button
    {
        constexpr char image[] = "data/image/002_05.png";                           //通常時の画像
        constexpr char imageClick[] = "data/image/002_05_click.png";                //クリック時の画像
        constexpr char imageHover[] = "data/image/002_05_hover.png";                //上に乗せてるときの画像

        constexpr char fontKey[] = "tutoCheck_button";                              //フォントのキー
        constexpr char fontPath[] = "data/font/03スマートフォントUI.otf";           //フォントのパス
        constexpr char fontName[] = "03スマートフォントUI";                         //フォント名
        constexpr int fontSize = 30;                                                //フォントのサイズ
        constexpr int fontThick = 10;                                               //フォントの太さ

        constexpr unsigned int textColor = 0x000000;
        constexpr unsigned int edgeColor = 0xffffff;

        constexpr Vector2Dbl clickOffset = { 0.0,10.0 };

        constexpr Vector2Dbl basePos = { 512.0,450.0 };
        constexpr Vector2Dbl interval = { 160.0,0.0 };

        namespace yes
        {
            constexpr Vector2Dbl pos = basePos - interval;

            constexpr char text[] = "はい";
            constexpr char nextMap[] = "data/map/tutorial1.json";
        }

        namespace no
        {
            constexpr Vector2Dbl pos = basePos + interval;

            constexpr char text[] = "いいえ";
            constexpr char nextMap[] = "data/map/select1.json";
            //constexpr char nextMap[] = "data/map/map1-1_1.json";
        }
    }
}

using namespace tutoCheck_const;

TutorialCheckScene::TutorialCheckScene(std::shared_ptr<SceneArgsStruct::TutorialCheckArgs> args) :
    BaseScene(args)
{
    Init();
    InitUI();
}

TutorialCheckScene::~TutorialCheckScene()
{
}

bool TutorialCheckScene::Init(void)
{
    return true;
}

bool TutorialCheckScene::InitUI(void)
{
    lpFontMng.GetID(button::fontKey, button::fontPath, button::fontName, button::fontSize, button::fontThick, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

    auto windowPtr = std::make_unique<ImagePanel>(Vector2Dbl(),
        TextOnGraphPanel()(imagePanel::text, imagePanel::image, button::fontKey, 0xffffff, 0x000000, Vector2Dbl(0.0, -40.0)));
    windowPtr->SetCC(imagePanel::pos);

    auto yesPtr = std::make_unique<NormalButton>(
        button::yes::pos, button::yes::text, button::fontKey, button::textColor, button::edgeColor,
        button::image, button::imageHover, button::imageClick,
        std::make_unique<ToNextSceneBC>(SceneID::Game, TransitionID::FadeM,
            std::make_shared<SceneArgsStruct::GameArgs>(button::yes::nextMap, true),
            std::make_shared<SceneArgsStruct::Transition::FadeMArgs>("data/image/mission_bg.png")),
        button::clickOffset);

    auto noPtr = std::make_unique<NormalButton>(
        button::no::pos, button::no::text, button::fontKey, button::textColor, button::edgeColor,
        button::image, button::imageHover, button::imageClick,
        std::make_unique<ToNextSceneBC>(SceneID::Game, TransitionID::FadeIO,
            std::make_shared<SceneArgsStruct::GameArgs>(button::no::nextMap, true),
            std::make_shared<SceneArgsStruct::Transition::FadeIOArgs>()),
        button::clickOffset);

    uiCtrl_.SetUI(std::move(windowPtr));
    uiCtrl_.SetUI(std::move(yesPtr));
    uiCtrl_.SetUI(std::move(noPtr));

    return true;
}

uniBaseScene TutorialCheckScene::Update(double delta, uniBaseScene ownScene)
{
    uiCtrl_.Update(delta);

    DrawOwnScreen();
    return ownScene;
}

void TutorialCheckScene::DrawOwnScreen(void)
{
    SetDrawScreen(scrID_);
    ClsDrawScreen();

    uiCtrl_.Draw();
}
