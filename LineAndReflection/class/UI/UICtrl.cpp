#include "../scene/SceneMng.h"
#include "UICtrl.h"
#include "UIObj/BaseUI.h"

UICtrl::UICtrl()
{
    Init();
}

UICtrl::~UICtrl()
{
}

bool UICtrl::Init(void)
{
    controller_ = lpSceneMng.GetController();
    return true;
}

void UICtrl::Update(double delta)
{
    for (auto& uiPtr : uiList_)
    {
        uiPtr->Update(delta);
    }

    auto pos = controller_->GetPos();

    //UI‚»‚ê‚¼‚ê‚É‘Î‚µ‚ÄƒŒƒC‚ð”ò‚Î‚·
    for (auto revItr = uiList_.rbegin(); revItr != uiList_.rend(); ++revItr)
    {
        if ((*revItr)->IsIntoMousePos(pos))
        {
            (*revItr)->SpotUpdate(controller_);
            break;
        }
    }
}

void UICtrl::Draw(void)
{
    for (auto& uiPtr : uiList_)
    {
        uiPtr->Draw();
    }
}

void UICtrl::SetUI(UIPtr uiPtr)
{
    uiList_.emplace_back(std::move(uiPtr));
}

UIList& UICtrl::GetUIList(void)
{
    return uiList_;
}
