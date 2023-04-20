#include "SceneMng.h"
#include "../common/ImageMng.h"
#include "../common/FontMng.h"
#include "../common/SoundMng.h"
#include "OptionScene.h"
#include "../UI/UIObj/RadioButton.h"
#include "../UI/UIObj/NormalButton.h"
#include "../UI/UIObj/ButtonCommand/ToNextSceneBC.h"
#include "../UI/UIObj/ImagePanel.h"
#include "../UI/UIObj/SeekBar.h"
#include "../common/Utility.h"

namespace optscene_const
{
    constexpr char bgPath[] = "data/image/opt_bg.png";

    constexpr char fontKey[] = "opt_ret_button";                                //�t�H���g�̃L�[
    constexpr char fontPath[] = "data/font/03�X�}�[�g�t�H���gUI.otf";           //�t�H���g�̃p�X
    constexpr char fontName[] = "03�X�}�[�g�t�H���gUI";                         //�t�H���g��
    constexpr int fontSize = 30;                                                //�t�H���g�̃T�C�Y
    constexpr int fontThick = 10;                                               //�t�H���g�̑���

    constexpr unsigned int textColor = 0x000000;
    constexpr unsigned int edgeColor = 0xffffff;

    namespace imagePanel
    {
        constexpr char image[] = "data/image/window_frame.png";
        constexpr Vector2Dbl pos = { 512.0,384.0 };
    }

    //�{�^���n
    namespace button
    {
        constexpr char image[] = "data/image/004_01.png";                           //�ʏ펞�̉摜
        constexpr char imageClick[] = "data/image/004_01_click.png";                //�N���b�N���̉摜
        constexpr char imageHover[] = "data/image/004_01_hover.png";                //��ɏ悹�Ă�Ƃ��̉摜

        constexpr unsigned int textColor = 0x000000;
        constexpr unsigned int edgeColor = 0xffffff;

        constexpr Vector2Dbl clickOffset = { 0.0,5.0 };

        namespace ret
        {
            constexpr char text[] = "�߂�";
            constexpr Vector2Dbl pos = { 40.0,40.0 };
        }
    }

    namespace selKey_button
    {
        constexpr Vector2Dbl basePos = { 600.0,300.0 };
        constexpr Vector2Dbl interval = { 80.0,0.0 };

        constexpr char text[] = "�W�����v�L�[�F";
        constexpr Vector2Dbl textPos = basePos - Vector2Dbl{ 400.0, 15.0 };

        namespace space
        {
            constexpr int key = KEY_INPUT_SPACE;
            constexpr char text[] = "SPACE�L�[";
            constexpr Vector2Dbl pos = basePos - interval;
        }

        namespace w
        {
            constexpr int key = KEY_INPUT_W;
            constexpr char text[] = "W�L�[";
            constexpr Vector2Dbl pos = basePos + interval;
        }
    }

    namespace volume_bar
    {
        constexpr Vector2Dbl basePos = { 600.0,400.0 };
        constexpr Vector2Dbl interval = { 180.0,0.0 };
        constexpr Vector2Dbl firstPos = basePos - interval;
        constexpr Vector2Dbl endPos = basePos + interval;

        constexpr char text[] = "���ʁF";
        constexpr Vector2Dbl textPos = basePos - Vector2Dbl{ 300.0, 15.0 };
    }
}

using namespace optscene_const;

OptionScene::OptionScene(std::shared_ptr<SceneArgsStruct::OptionArgs> args) :
    BaseScene(args)
{
    Init();
    InitUI();
}

OptionScene::~OptionScene()
{
    unsigned int keyID = KEY_INPUT_SPACE;

    for (auto& uiObj : uiCtrl_.GetUIList())
    {
        if (uiObj->GetUIType() != UIType::RadioButton)
        {
            continue;
        }

        keyID = atoi(std::unique_ptr<RadioButton>(dynamic_cast<RadioButton*>(uiObj.release()))->GetNowSelectKey().c_str());
    }

    lpSceneMng.GetController()->SetID(InputID::UP, keyID);
}

bool OptionScene::Init(void)
{
    //lpImageMng.GetID(bgPath);
    return true;
}

bool OptionScene::InitUI(void)
{
    //���O�ɓo�^
    lpFontMng.GetID(fontKey, fontPath, fontName, fontSize, fontThick, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

    auto windowPtr = std::make_unique<ImagePanel>(Vector2Dbl(), imagePanel::image);
    windowPtr->SetCC(imagePanel::pos);

    uiCtrl_.SetUI(std::move(windowPtr));

    auto retPtr = std::make_unique<NormalButton>(
        button::ret::pos, button::ret::text, fontKey, button::textColor, button::edgeColor,
        button::image, button::imageHover, button::imageClick,
        std::make_unique<ToNextSceneBC>(SceneID::Title, TransitionID::FadeIO,
            std::make_shared<SceneArgsStruct::TutorialCheckArgs>(),
            std::make_shared<SceneArgsStruct::Transition::FadeIOArgs>()),
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

    return true;
}

uniBaseScene OptionScene::Update(double delta, uniBaseScene ownScene)
{
    uiCtrl_.Update(delta);
    DrawOwnScreen();

    return ownScene;
}

void OptionScene::DrawOwnScreen(void)
{
    SetDrawScreen(scrID_);
    ClsDrawScreen();

    DrawGraph(0, 0, lpImageMng.GetID(bgPath)[0], true);
    uiCtrl_.Draw();

    DrawStringToHandle(
        static_cast<int>(selKey_button::textPos.x), static_cast<int>(selKey_button::textPos.y),
        selKey_button::text, 0xffffff, lpFontMng.GetID(fontKey), 0x000000);

    DrawStringToHandle(
        static_cast<int>(volume_bar::textPos.x), static_cast<int>(volume_bar::textPos.y),
        volume_bar::text, 0xffffff, lpFontMng.GetID(fontKey), 0x000000);
}
