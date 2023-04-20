#include <DxLib.h>
#include "Square.h"
#include "../SceneMng.h"
#include "../../../_debug/_debugConOut.h"

Square::Square(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr <SceneArgsStruct::Transition::SquareArgs> args)
	:TransitionScene(std::move(beforeScene), std::move(nextScene), args),tTime(1)
{
	count_ = 0;
	count2_ = -5;

	auto windowSize = lpSceneMng.GetWindowSize();
	nextScr_ = MakeScreen(windowSize.x, windowSize.y, 255);

	chipSize_ = { 32,32 };
	viewArea_ = windowSize / chipSize_;
}

Square::~Square()
{
}

void Square::DrawOwnScreen(void)
{
	SetDrawScreen(nextScr_);
	ClsDrawScreen();
	nextScene_->DrawOwnScreen();
	nextScene_->Draw();

	SetDrawScreen(scrID_);
	ClsDrawScreen();

	if (count2_ < viewArea_.x * viewArea_.y * tTime)
	{
		beforeScene_->Draw();
		for (int x = 0; x < viewArea_.x; x++)
		{
			for (int y = 0; y < viewArea_.y; y++)
			{
				//TRACE("X:%d\n", x);
				//TRACE("Y:%d\n", y);
				if (x % 2)
				{
					int yR = viewArea_.y - y;
					DrawCloseTile(x, y, count_);
				}
				else
				{
					DrawCloseTile(x, y, count_);
				}
			}
		}
	}

	if (count2_ && count2_ < viewArea_.x * viewArea_.y * tTime)
	{
		for (int x = 0; x < viewArea_.x; x++)
		{
			for (int y = 0; y < viewArea_.y; y++)
			{
				//TRACE("X:%d\n", x);
				//TRACE("Y:%d\n", y);
				if (x % 2)
				{
					int yR = viewArea_.y - y;
					DrawOpenTile(x, y, count2_);
				}
				else
				{
					DrawOpenTile(x, y, count2_);
				}
			}
		}
	}

}

bool Square::UpdateTransition(double delta)
{
	DrawOwnScreen();

	count_++;
	count2_++;

	return (count2_ > (viewArea_.x * viewArea_.y * tTime));
}

void Square::DrawCloseTile(int x, int y, int count)
{
	int num;

	if (x % 2)
	{
		//1‚Ìê‡
		num = (x * viewArea_.y) + ((viewArea_.y - 1) - y);
	}
	else
	{
		//0‚Ìê‡
		num = (x * viewArea_.y) + y;
	}

	if (count / tTime >= num)
	{
		DrawBox(
			x * chipSize_.x, y * chipSize_.y,
			(x + 1) * chipSize_.x, (y + 1) * chipSize_.y,
			0xffffff, true);
	}
	else
	{
		//‰½‚à•`‰æ‚µ‚È‚¢
	}
}

void Square::DrawOpenTile(int x, int y, int count)
{
	int num;

	if (x % 2)
	{
		//1‚Ìê‡
		num = (x * viewArea_.y) + ((viewArea_.y - 1) - y);
	}
	else
	{
		//0‚Ìê‡
		num = (x * viewArea_.y) + y;
	}

	if (count / tTime >= num)
	{
		DrawRectGraph(
			x * chipSize_.x,
			y * chipSize_.y,
			x * chipSize_.x,
			y * chipSize_.y,
			chipSize_.x, chipSize_.y,
			nextScr_, true, false
		);
	}
	else
	{
		//‰½‚à•`‰æ‚µ‚È‚¢
	}
}
