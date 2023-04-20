#include <DxLib.h>
#include "PlayMenu.h"
#include "TemporaryID.h"
#include "../../UI/UIObj/NormalButton.h"
#include "../../UI/UIObj/ImagePanel.h"
#include "../../UI/UIObj/ButtonCommand/ButtonCommandFunc.h"
#include "../../UI/UIObj/ButtonCommand/ToNextSceneBC.h"
#include "../../UI/UIObj/ButtonCommand/ToNextTemporaryBC.h"

namespace playMenu_const
{
	namespace gauss
	{
		constexpr int pixelWidth = 32;
		constexpr int param = 1400;
	}

	namespace imagePanel
	{
		constexpr char image[] = "data/image/window_frame.png";
		constexpr Vector2Dbl pos = { 512.0,384.0 };
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

		constexpr Vector2Dbl basePos = { 512.0,300.0 };
		constexpr Vector2Dbl interval = { 0.0,110.0 };

		namespace go_mapSelect
		{
			constexpr char text[] = "�}�b�v�I���ɖ߂�";
			constexpr Vector2Dbl pos = basePos;

			constexpr char mapSelect[] = "data/map/select1.json";
		}

		namespace opt
		{
			constexpr char text[] = "�I�v�V����";
			constexpr Vector2Dbl pos = go_mapSelect::pos + interval;
		}

		namespace ret
		{
			constexpr char text[] = "�߂�";
			constexpr Vector2Dbl pos = opt::pos + Vector2Dbl{0.0, 140.0};
		}
	}
}

using namespace playMenu_const;

PlayMenu::PlayMenu(uniBaseScene beforeScene, std::shared_ptr<SceneArgsStruct::Temporary::PlayMenuArgs> args) :
	Temporary(std::move(beforeScene), args)
{
	retFlg_ = false;
	InitUI();
}

PlayMenu::~PlayMenu()
{
}

void PlayMenu::DrawOwnScreen(void)
{
	SetDrawScreen(scrID_);
	ClsDrawScreen();

	beforeScene_->Draw();

	GraphFilter(scrID_, DX_GRAPH_FILTER_GAUSS, gauss::pixelWidth, gauss::param);

	uictrl_.Draw();
}

bool PlayMenu::UpdateTemporary(double delta)
{
	retFlg_ = false;

	uictrl_.Update(delta);

	DrawOwnScreen();
	return retFlg_;
}

void PlayMenu::InitUI(void)
{
	auto windowPtr = std::make_unique<ImagePanel>(Vector2Dbl(), imagePanel::image);
	windowPtr->SetCC(imagePanel::pos);
	uictrl_.SetUI(std::move(windowPtr));

	auto goMapSelectPtr = std::make_unique<NormalButton>(
		button::go_mapSelect::pos, button::go_mapSelect::text, button::fontKey, button::textColor, button::edgeColor,
		button::image, button::imageHover, button::imageClick,
		std::make_unique<ToNextSceneBC>(SceneID::Game, TransitionID::FadeIO,
			std::make_shared<SceneArgsStruct::GameArgs>(button::go_mapSelect::mapSelect),
			std::make_shared<SceneArgsStruct::Transition::FadeIOArgs>()),
		button::clickOffset);

	uictrl_.SetUI(std::move(goMapSelectPtr));

	auto optPtr = std::make_unique<NormalButton>(
		button::opt::pos, button::opt::text, button::fontKey, button::textColor, button::edgeColor,
		button::image, button::imageHover, button::imageClick,
		std::make_unique<ToNextTemporaryBC>(
			TemporaryID::OptionMenu,
			std::make_shared<SceneArgsStruct::Temporary::OptionMenuArgs>()),
		button::clickOffset);

	uictrl_.SetUI(std::move(optPtr));

	auto retPtr = std::make_unique<NormalButton>(
		button::ret::pos, button::ret::text, button::fontKey, button::textColor, button::edgeColor,
		button::image, button::imageHover, button::imageClick,
		std::make_unique<ButtonCommandFunc>(
			[&](Button& button) { retFlg_ = true; }),
		button::clickOffset);

	uictrl_.SetUI(std::move(retPtr));
}
