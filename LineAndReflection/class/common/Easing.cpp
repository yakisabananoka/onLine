#include <cmath>
#include "Easing.h"

namespace easing_const
{
    constexpr double coe1 = 1.70158;
    constexpr double coe2 = coe1 * 1.525;
    constexpr double coe3 = coe1 + 1.0;
}

using namespace easing_const;

double Easing::InQuad(double time, double startVal, double deltaVal, double total) const
{
    time /= total;
    return deltaVal * time * time + startVal;
}

double Easing::InCubic(double time, double startVal, double deltaVal, double total) const
{
    time /= total;
    return deltaVal * time * time * time + startVal;
}

double Easing::InQuart(double time, double startVal, double deltaVal, double total) const
{
    time /= total;
    return deltaVal * time * time * time * time + startVal;
}

double Easing::InQuint(double time, double startVal, double deltaVal, double total) const
{
    time /= total;
    return deltaVal * time * time * time * time * time + startVal;
}

double Easing::InExpo(double time, double startVal, double deltaVal, double total) const
{
    return deltaVal * pow(2.0, (10.0 * (time / total - 1.0))) + startVal;
}

double Easing::InCirc(double time, double startVal, double deltaVal, double total) const
{
    time /= total;
    return -deltaVal * (sqrt(1.0 - time * time) - 1.0) + startVal;
}

double Easing::InBack(double time, double startVal, double deltaVal, double total) const
{
    time /= total;

    return deltaVal * (coe3 * time * time * time - coe1 * time * time) + startVal;
}

double Easing::OutQuad(double time, double startVal, double deltaVal, double total) const
{
    time /= total;
    return -deltaVal * time * (time - 2.0) + startVal;
}

double Easing::OutCubic(double time, double startVal, double deltaVal, double total) const
{
    time /= total;
    time -= 1.0;
    return deltaVal * (time * time * time + 1.0) + startVal;
}

double Easing::OutQuart(double time, double startVal, double deltaVal, double total) const
{
    time /= total;
    time -= 1.0;
    return -deltaVal * (time * time * time * time - 1.0) * startVal;
}

double Easing::OutQuint(double time, double startVal, double deltaVal, double total) const
{
    time /= total;
    time -= 1.0;
    return deltaVal * (time * time * time * time * time + 1.0) + startVal;
}

double Easing::OutExpo(double time, double startVal, double deltaVal, double total) const
{
    return deltaVal * (-pow(2.0, -10.0 * time / total) + 1.0) + startVal;
}

double Easing::OutCirc(double time, double startVal, double deltaVal, double total) const
{
    time /= total;
    time -= 1.0;
    return deltaVal * sqrt(1.0 - time * time) + startVal;
}

double Easing::OutBack(double time, double startVal, double deltaVal, double total) const
{
    time /= total;
    return deltaVal * (1.0 + coe3 * pow(time - 1.0, 3) * coe1 * pow(time - 1.0, 2)) + startVal;
}

double Easing::InOutQuad(double time, double startVal, double deltaVal, double total) const
{
    time /= total / 2.0;
    if (time < 1.0)
    {
        return deltaVal / 2.0 * time * time + startVal;
    }
    time -= 1.0;
    return -deltaVal / 2.0 * (time * (time - 2.0) - 1.0) + startVal;
}

double Easing::InOutCubic(double time, double startVal, double deltaVal, double total) const
{
    time /= total / 2.0;
    if (time < 1.0)
    {
        return deltaVal / 2.0 * time * time * time + startVal;
    }

    time -= 2.0;

    return deltaVal / 2.0 * (time * time * time + 2.0) + startVal;
}

double Easing::InOutQuart(double time, double startVal, double deltaVal, double total) const
{
    time /= total / 2.0;
    if (time < 1.0)
    {
        return deltaVal / 2.0 * time * time * time * time + startVal;
    }
    time -= 2.0;
    return -deltaVal / 2.0 * (time * time * time * time - 2.0) + startVal;
}

double Easing::InOutQuint(double time, double startVal, double deltaVal, double total) const
{
    time /= total / 2.0;
    if (time < 1.0)
    {
        return deltaVal / 2.0 * time * time * time * time * time + startVal;
    }
    time -= 2.0;
    return deltaVal / 2.0 * (time * time * time * time * time + 2.0) + startVal;
}

double Easing::InOutExpo(double time, double startVal, double deltaVal, double total) const
{
    time /= total / 2.0;
    if (time < 1.0)
    {
        return deltaVal / 2.0 * pow(2.0, 10.0 * (time - 1.0)) + startVal;
    }
    time -= 1.0;
    return deltaVal / 2.0 * (-pow(2.0, -10.0 * time) + 2.0) + startVal;
}

double Easing::InOutCirc(double time, double startVal, double deltaVal, double total) const
{
    time /= total / 2.0;
    if (time < 1.0)
    {
        return -deltaVal / 2.0 * (sqrt(1.0 - time * time) - 1.0) + startVal;
    }
    time -= 2.0;
    return deltaVal / 2.0 * (sqrt(1.0 - time * time) + 1.0) + startVal;
}

double Easing::InOutBack(double time, double startVal, double deltaVal, double total) const
{
    time /= total / 2.0;
    if (time < 1.0)
    {
        return deltaVal / 2.0 * (pow(time, 2) * ((coe2 + 1.0) * time - coe2)) + startVal;
    }
    time -= 2.0;
    return deltaVal / 2.0 * (pow(time, 2) * ((coe2 + 1.0) * time - coe2) + 2.0) + startVal;
}
