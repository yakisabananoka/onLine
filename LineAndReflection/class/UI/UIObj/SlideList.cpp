#include <sstream>
#include <DxLib.h>
#include "../../common/ImageMng.h"
#include "SlideList.h"

namespace slideList_cost
{
}

SlideList::SlideList(Rect range, std::string key) :
    BaseUI(range), scrKey_(key)
{
    std::stringstream ss(key);
    ss << "_slideList";

    if (!lpImageMng.ExistID(scrKey_))
    {
        lpImageMng.GetID(scrKey_, MakeScreen(static_cast<int>(range_.size.x), static_cast<int>(range_.size.y), true));
    }
}

SlideList::~SlideList()
{
}

void SlideList::Init(void)
{
}

void SlideList::InitUI(void)
{
}

void SlideList::Update(double delta)
{
}

void SlideList::SpotUpdate(std::shared_ptr<Controller> controller)
{
}

void SlideList::Draw(void)
{
}

bool SlideList::IsIntoMousePos(const Vector2Dbl& mousePos)
{
    return false;
}
