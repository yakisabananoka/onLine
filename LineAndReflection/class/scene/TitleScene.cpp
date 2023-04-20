#include <vector>
#include <DxLib.h>
#include "SceneMng.h"
#include "../common/ImageMng.h"
#include "../common/SoundMng.h"
#include "../common/FontMng.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneArgsStruct.h"
#include "temporary/TemporaryID.h"
#include "../UI/UIObj/NormalButton.h"
#include "../UI/UIObj/ButtonCommand/ButtonCommandFunc.h"
#include "../UI/UIObj/ButtonCommand/ToNextSceneBC.h"
#include "../UI/UIObj/ImagePanel.h"
#include "../../_debug/_debugConOut.h"

#include "../UI/UIObj/ButtonCommand/ToNextTemporaryBC.h"

namespace title_const
{
    constexpr char bgmKey[] = "title";

    
    namespace imagePanel
    {
        constexpr char logoKey[] = "data/image/logo.png";
        constexpr Vector2Dbl pos = { 512.0,200.0 };
    }

    //�{�^���n
    namespace button
    {
        constexpr char image[] = "data/image/002_05.png";                           //�ʏ펞�̉摜
        constexpr char imageClick[] = "data/image/002_05_click.png";                //�N���b�N���̉摜
        constexpr char imageHover[] = "data/image/002_05_hover.png";                //��ɏ悹�Ă�Ƃ��̉摜
        
        constexpr char fontKey[] = "title_button";                                  //�t�H���g�̃L�[
        constexpr char fontPath[] = "data/font/03�X�}�[�g�t�H���gUI.otf";           //�t�H���g�̃p�X
        constexpr char fontName[] = "03�X�}�[�g�t�H���gUI";                         //�t�H���g��
        constexpr int fontSize = 30;                                                //�t�H���g�̃T�C�Y
        constexpr int fontThick = 10;                                               //�t�H���g�̑���

        constexpr unsigned int textColor = 0x000000;
        constexpr unsigned int edgeColor = 0xffffff;

        constexpr Vector2Dbl clickOffset = { 0.0,10.0 };

        constexpr Vector2Dbl basePos = { 512.0,470.0 };
        constexpr Vector2Dbl interval = { 0.0,110.0 };

        namespace start
        {
            constexpr char text[] = "�Q�[�����n�߂�";
            constexpr Vector2Dbl pos = basePos;
        }

        namespace opt
        {
            constexpr char text[] = "�I�v�V����";
            constexpr Vector2Dbl pos = start::pos + interval;
        }

        namespace close
        {
            constexpr char text[] = "�I������";
            constexpr Vector2Dbl pos = opt::pos + interval;
        }
    }
    
}

using namespace title_const;

TitleScene::TitleScene(std::shared_ptr<SceneArgsStruct::TitleArgs> args) :
    BaseScene(args)
{
    TRACE("TitleScene�𐶐�\n");
    gameScene_ = std::make_unique<GameScene>(std::make_shared<SceneArgsStruct::GameArgs>("data/map/title.json", false, false));
    Init();
}

TitleScene::~TitleScene()
{
    TRACE("TitleScene��j��\n");
}

bool TitleScene::Init(void)
{
    lpSoundMng.LoadSound(bgmKey);
    controller_ = lpSceneMng.GetController();

    InitUI();

    return true;
}

bool TitleScene::InitUI(void)
{
    //���O�ɓo�^
    lpFontMng.GetID(button::fontKey, button::fontPath, button::fontName, button::fontSize, button::fontThick, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

    //UI�̓o�^
    auto logoPtr = std::make_unique<ImagePanel>(Vector2Dbl(), imagePanel::logoKey);
    logoPtr->SetCC(imagePanel::pos);
    
    //�X�^�[�g�{�^��
    auto startPtr = std::make_unique<NormalButton>(
        button::start::pos, button::start::text, button::fontKey, button::textColor, button::edgeColor,
        button::image, button::imageHover, button::imageClick,
        std::make_unique<ToNextSceneBC>(SceneID::TutorialCheck, TransitionID::FadeIO,
            std::make_shared<SceneArgsStruct::TutorialCheckArgs>(),
            std::make_shared<SceneArgsStruct::Transition::FadeIOArgs>()),
        button::clickOffset);


    //�I���{�^��
    auto closePtr = std::make_unique<NormalButton>(
        button::close::pos, button::close::text, button::fontKey, button::textColor, button::edgeColor,
        button::image, button::imageHover, button::imageClick,
        std::make_unique<ButtonCommandFunc>([](Button& button) {exit(1); }),
        button::clickOffset);

    //�I�v�V����
    auto optPtr = std::make_unique<NormalButton>(
        button::opt::pos, button::opt::text, button::fontKey, button::textColor, button::edgeColor,
        button::image, button::imageHover, button::imageClick,
        std::make_unique<ToNextTemporaryBC>(
            TemporaryID::OptionMenu,
            std::make_shared<SceneArgsStruct::Temporary::OptionMenuArgs>()),
        button::clickOffset);

    uiCtrl_.SetUI(std::move(logoPtr));
    uiCtrl_.SetUI(std::move(startPtr));
    uiCtrl_.SetUI(std::move(closePtr));
    uiCtrl_.SetUI(std::move(optPtr));

    return true;
}

uniBaseScene TitleScene::Update(double delta, uniBaseScene ownScene)
{
    uiCtrl_.Update(delta);
    gameScene_ = gameScene_->Update(delta, std::move(gameScene_));

    if (nextScene_ != nullptr)
    {
        return std::move(nextScene_);
    }

    DrawOwnScreen();
    return ownScene;
}

void TitleScene::DrawOwnScreen(void)
{
    SetDrawScreen(scrID_);
    ClsDrawScreen();

    //DrawGraph(0, 0, lpImageMng.GetID(bgPath)[0], true);
    gameScene_->Draw();
    uiCtrl_.Draw();
}

void TitleScene::PlaySceneBGM(void)
{
    lpSoundMng.PlayBGM(bgmKey);
}

