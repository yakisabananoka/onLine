#include <DxLib.h>
#include "HowToPlay.h"
#include "../../UI/UIObj/NormalButton.h"
#include "../../UI/UIObj/ImagePanel.h"
#include "../../UI/UIObj/ButtonCommand/ButtonCommandFunc.h"

namespace howtoplay_const
{
	namespace imagePanel
	{
		constexpr char image[] = "data/image/howtoplay.png";
		constexpr Vector2Dbl pos = { 512.0,384 };
	}

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

		constexpr Vector2Dbl basePos = { 512.0,700.0 };
		constexpr Vector2Dbl interval = { 0.0,110.0 };

		namespace ret
		{
			constexpr char text[] = "�߂�";
			constexpr Vector2Dbl pos = basePos;
		}
	}
}

using namespace howtoplay_const;

HowToPlay::HowToPlay(uniBaseScene beforeScene, std::shared_ptr<SceneArgsStruct::Temporary::HowToPlayArgs> args) :
    Temporary(std::move(beforeScene), args)
{
    retFlg_ = false;
    InitUI();
}

HowToPlay::~HowToPlay()
{
}

void HowToPlay::DrawOwnScreen(void)
{
    SetDrawScreen(scrID_);
    ClsDrawScreen();

    beforeScene_->Draw();

    uictrl_.Draw();
}

bool HowToPlay::UpdateTemporary(double delta)
{
    retFlg_ = false;

    uictrl_.Update(delta);

    DrawOwnScreen();
    return retFlg_;
}

void HowToPlay::InitUI(void)
{
	auto imagePtr = std::make_unique<ImagePanel>(Vector2Dbl(), imagePanel::image);
	imagePtr->SetCC(imagePanel::pos);

	uictrl_.SetUI(std::move(imagePtr));

	auto retPtr = std::make_unique<NormalButton>(
		button::ret::pos, button::ret::text, button::fontKey, button::textColor, button::edgeColor,
		button::image, button::imageHover, button::imageClick,
		std::make_unique<ButtonCommandFunc>([&](Button& button) { retFlg_ = true; }),
		button::clickOffset);

    uictrl_.SetUI(std::move(retPtr));
}
