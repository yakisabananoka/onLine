#pragma once
#include <string>
#include <sstream>
#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../common/FontMng.h"
#include "../common/shape/Rect.h"

//これらはあとでクラスに置き換え

//旧タイトル画面のボタンのパネル
struct GameStartPanel
{
	std::string operator()()
	{
		constexpr char key[] = "test_gamestart";
		constexpr double sizeX = 300;
		constexpr double sizeY = 100;
		constexpr char text[] = "GAME START!";
		constexpr double textSize = sizeY / 2.0;
		constexpr unsigned int color = 0xf0f0f0;

        if (lpImageMng.ExistID(key))
        {
            return key;
        }

        SetFontSize(static_cast<int>(textSize));

        Rect button = { Vector2Dbl(), { sizeX,sizeY } };

        int buffer = MakeScreen(static_cast<int>(button.size.x), static_cast<int>(button.size.y), true);
		SetDrawScreen(buffer);

        DrawBoxAA(
            static_cast<float>(button.Left()),
            static_cast<float>(button.Top()),
            static_cast<float>(button.Right()),
            static_cast<float>(button.Bottom()),
            color, true
        );
        DrawBoxAA(
            static_cast<float>(button.Left()),
            static_cast<float>(button.Top()),
            static_cast<float>(button.Right()),
            static_cast<float>(button.Bottom()),
            0x000000, false
        );

        auto width = GetDrawStringWidth(text, static_cast<int>(strlen(text)));
        DrawString(
            static_cast<int>(button.GetCC().x) - width / 2,
            static_cast<int>(button.GetCC().y - textSize / 2.0),
            text, 0x000000
        );

        lpImageMng.GetID(key, buffer);

        return key;
	}
};

//画像の上にテキストを乗せたものを登録
struct TextOnGraphPanel
{
    std::string operator()(std::string text, std::string imageKey, std::string fontKey, unsigned int textColor, unsigned int edgeColor, Vector2Dbl textOffset = Vector2Dbl())
    {
        std::stringstream key;
        key << text << imageKey;

        if (lpImageMng.ExistID(key.str()))
        {
            return key.str();
        }

        Rect button = { Vector2Dbl(),static_cast<Vector2Dbl>(lpImageMng.GetSize(imageKey)) };
        Rect textRange(
            button.GetCC(),
            static_cast<double>(GetDrawStringWidthToHandle(text.c_str(), static_cast<int>(strlen(text.c_str())), lpFontMng.GetID(fontKey))),
            static_cast<double>(GetFontSizeToHandle(lpFontMng.GetID(fontKey)))
        );
        int buffer = MakeScreen(static_cast<int>(button.size.x), static_cast<int>(button.size.y), true);
        SetDrawScreen(buffer);

        DrawGraph(0, 0, lpImageMng.GetID(imageKey)[0], true);
        DrawStringToHandle(
            static_cast<int>(textOffset.x + textRange.pos.x),
            static_cast<int>(textOffset.y + textRange.pos.y),
            text.c_str(), textColor, lpFontMng.GetID(fontKey), edgeColor
        );

        lpImageMng.GetID(key.str(), buffer);
        lpImageMng.GetSoftID(key.str(), LoadARGB8ColorSoftImage(imageKey.c_str()));

        return key.str();
    }
};
