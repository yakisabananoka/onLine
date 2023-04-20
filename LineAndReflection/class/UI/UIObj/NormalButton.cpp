#include "NormalButton.h"
#include "../../common/ImageMng.h"
#include "../../common/SoundMng.h"
#include "ButtonCommand/ChangeImageBC.h"
#include "ButtonCommand/PlaySEBC.h"
#include "../Panels.h"

namespace normalButton_const
{
    namespace sound
    {
        constexpr char hover[] = "button_hover";
        constexpr char click[] = "button_click";
    }
}

using namespace normalButton_const;

NormalButton::NormalButton(Vector2Dbl ccPos, const std::string& text, const std::string& fontKey, unsigned int textColor, unsigned int edgeColor,
    const std::string& normalImage, const std::string& hoverImage, const std::string& clickImage, ButtonCommandPtr command, Vector2Dbl clickOffset) :
    Button({}, normalImage)
{
    SetCC(ccPos);

    lpImageMng.GetID(normalImage);
    lpImageMng.GetID(hoverImage);
    lpImageMng.GetID(clickImage);
    
    lpSoundMng.LoadSound(sound::click);
    lpSoundMng.LoadSound(sound::hover);

    std::string defImageKey = TextOnGraphPanel()(text, normalImage, fontKey, textColor, edgeColor);

    SetCommand(Button::State::NowEnter, std::make_unique<ChangeImageBC>(TextOnGraphPanel()(text, hoverImage, fontKey, textColor, edgeColor)));
    SetCommand(Button::State::JustEnter, std::make_unique<PlaySEBC>(sound::hover));
    SetCommand(Button::State::NowLeave, std::make_unique<ChangeImageBC>(defImageKey));
    SetCommand(Button::State::NowOn, std::make_unique<ChangeImageBC>(TextOnGraphPanel()(text, clickImage, fontKey, textColor, edgeColor, clickOffset)));
    SetCommand(Button::State::JustOn, std::make_unique<PlaySEBC>(sound::click));
    SetCommand(Button::State::JustOff, std::move(command));
    
    SetImageKey(defImageKey);
}

NormalButton::~NormalButton()
{
}
