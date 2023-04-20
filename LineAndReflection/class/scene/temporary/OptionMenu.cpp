#include <DxLib.h>
#include "../SceneMng.h"
#include "../../common/ImageMng.h"
#include "../../common/FontMng.h"
#include "../../common/SoundMng.h"
#include "OptionMenu.h"
#include "../../UI/UIObj/RadioButton.h"
#include "../../UI/UIObj/NormalButton.h"
#include "../../UI/UIObj/ButtonCommand/ToNextSceneBC.h"
#include "../../UI/UIObj/ButtonCommand/ButtonCommandFunc.h"
#include "../../UI/UIObj/ImagePanel.h"
#include "../../UI/UIObj/SeekBar.h"
#include "../../common/Utility.h"

namespace optmenu_const
{
    constexpr char bgPath[] = "data/image/opt_bg.png";

    constexpr char fontKey[] = "opt_ret_button";                                //フォントのキー
    constexpr char fontPath[] = "data/font/03スマートフォントUI.otf";           //フォントのパス
    constexpr char fontName[] = "03スマートフォントUI";                         //フォント名
    constexpr int fontSize = 30;                                                //フォントのサイズ
    constexpr int fontThick = 10;                                               //フォントの太さ

    constexpr unsigned int textColor = 0x000000;
    constexpr unsigned int edgeColor = 0xffffff;

    namespace imagePanel
    {
        constexpr char image[] = "data/image/window_frame.png";
        constexpr Vector2Dbl pos = { 512.0,384.0 };
    }

    //ボタン系
    namespace button
    {
        constexpr char image[] = "data/image/002_05.png";                           //通常時の画像
        constexpr char imageClick[] = "data/image/002_05_click.png";                //クリック時の画像
        constexpr char imageHover[] = "data/image/002_05_hover.png";                //上に乗せてるときの画像

        constexpr unsigned int textColor = 0x000000;
        constexpr unsigned int edgeColor = 0xffffff;

        constexpr Vector2Dbl clickOffset = { 0.0,5.0 };
        namespace ret
        {
            constexpr char text[] = "戻る";
            constexpr Vector2Dbl pos = { 512.0,550.0 };
        }
    }

    namespace selKey_button
    {
        constexpr Vector2Dbl basePos = { 600.0,300.0 };
        constexpr Vector2Dbl interval = { 80.0,0.0 };

        constexpr char text[] = "ジャンプキー：";
        constexpr Vector2Dbl textPos = basePos - Vector2Dbl{ 400.0, 15.0 };

        namespace space
        {
            constexpr int key = KEY_INPUT_SPACE;
            constexpr char text[] = "SPACEキー";
            constexpr Vector2Dbl pos = basePos - interval;
        }

        namespace w
        {
            constexpr int key = KEY_INPUT_W;
            constexpr char text[] = "Wキー";
            constexpr Vector2Dbl pos = basePos + interval;
        }
    }

    namespace volume_bar
    {
        constexpr Vector2Dbl basePos = { 600.0,400.0 };
        constexpr Vector2Dbl interval = { 180.0,0.0 };
        constexpr Vector2Dbl firstPos = basePos - interval;
        constexpr Vector2Dbl endPos = basePos + interval;

        constexpr char text[] = "音量：";
        constexpr Vector2Dbl textPos = basePos - Vector2Dbl{ 300.0, 15.0 };
    }
}

using namespace optmenu_const;


OptionMenu::OptionMenu(uniBaseScene beforeScene, std::shared_ptr<SceneArgsStruct::Temporary::OptionMenuArgs> args):
    Temporary(std::move(beforeScene), args)
{
    retFlg_ = false;
    InitUI();
}

OptionMenu::~OptionMenu()
{
}

void OptionMenu::DrawOwnScreen(void)
{
    SetDrawScreen(scrID_);
    ClsDrawScreen();

    beforeScene_->Draw();

    uiCtrl_.Draw();

    DrawStringToHandle(
        static_cast<int>(selKey_button::textPos.x), static_cast<int>(selKey_button::textPos.y),
        selKey_button::text, 0xffffff, lpFontMng.GetID(fontKey), 0x000000);

    DrawStringToHandle(
        static_cast<int>(volume_bar::textPos.x), static_cast<int>(volume_bar::textPos.y),
        volume_bar::text, 0xffffff, lpFontMng.GetID(fontKey), 0x000000);
}

bool OptionMenu::UpdateTemporary(double delta)
{
    retFlg_ = false;

    uiCtrl_.Update(delta);

    DrawOwnScreen();
    return retFlg_;
}

void OptionMenu::InitUI(void)
{
    //事前に登録
    lpFontMng.GetID(fontKey, fontPath, fontName, fontSize, fontThick, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

    auto windowPtr = std::make_unique<ImagePanel>(Vector2Dbl(), imagePanel::image);
    windowPtr->SetCC(imagePanel::pos);
    uiCtrl_.SetUI(std::move(windowPtr));

    auto retPtr = std::make_unique<NormalButton>(
        button::ret::pos,
        button::ret::text, fontKey, button::textColor, button::edgeColor,
        button::image, button::imageHover, button::imageClick,
        std::make_unique<ButtonCommandFunc>(
            [&](Button& button) { retFlg_ = true; }),
        button::clickOffset);
    uiCtrl_.SetUI(std::move(retPtr));

    auto selKeyPtr = std::make_unique<RadioButton>(fontKey);
    selKeyPtr->SetChildButton(std::to_string(selKey_button::space::key), selKey_button::space::text, selKey_button::space::pos.x, selKey_button::space::pos.y, textColor, edgeColor);
    selKeyPtr->SetChildButton(std::to_string(selKey_button::w::key), selKey_button::w::text, selKey_button::w::pos.x, selKey_button::w::pos.y, textColor, edgeColor);

    selKeyPtr->SetSelectKey(std::to_string(lpSceneMng.GetController()->GetID(InputID::UP)));

    uiCtrl_.SetUI(std::move(selKeyPtr));

    auto volumeBar = std::make_unique<SeekBar>(volume_bar::firstPos, volume_bar::endPos);
    volumeBar->SetValue(lpSoundMng.GetVolume());

    auto volSetter = [&](double vol) {
        lpSoundMng.SetVolume(vol);
    };

    volumeBar->SetUpdateCallback(volSetter);

    uiCtrl_.SetUI(std::move(volumeBar));

    return;

}
