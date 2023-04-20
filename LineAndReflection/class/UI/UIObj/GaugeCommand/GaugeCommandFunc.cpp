#include "../Gauge.h"
#include "GaugeCommandFunc.h"

GaugeCommandFunc::GaugeCommandFunc(CallbackGCFunc func) :
	func_(func)
{
}

GaugeCommandFunc::~GaugeCommandFunc()
{
}

void GaugeCommandFunc::Execute(Gauge& gauge)
{
	func_(gauge);
}
