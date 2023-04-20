#include <DxLib.h>
#include "FontMng.h"
#include "../../_debug/_DebugConOut.h"

int FontMng::GetID(std::string fontKey)
{
    if (!fontMap_.count(fontKey))
    {
        return -1;
    }

    return fontMap_[fontKey].second;
}

int FontMng::GetID(std::string fontKey, std::string path, std::string fontName, int size, int thick)
{
    return GetID(fontKey, path, fontName, size, thick, DX_FONTTYPE_ANTIALIASING_8X8);
}

int FontMng::GetID(std::string fontKey, std::string path, std::string fontName, int size, int thick, int fontType)
{
    if (!fontMap_.count(fontKey))
    {
        //assert(AddFontResourceEx(path.c_str(), FR_PRIVATE, NULL));
        AddFontResourceEx(path.c_str(), FR_PRIVATE, NULL);
        TRACE("「%s」のフォント読み込み\n", fontName.c_str());
        fontMap_.try_emplace(fontKey, std::make_pair(path, CreateFontToHandle(fontName.c_str(), size, thick, fontType)));
    }

    return fontMap_[fontKey].second;
}

FontMng::~FontMng()
{
    for (const auto& fntData : fontMap_)
    {
        RemoveFontResource(fntData.first.c_str());
    }
}
