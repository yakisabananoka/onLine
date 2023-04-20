#pragma once
#include <memory>

class Gauge;
class GaugeCommand;

using GaugeCommandPtr = std::unique_ptr<GaugeCommand>;

class GaugeCommand
{
public:
	GaugeCommand() {};
	~GaugeCommand() {};

	virtual void Execute(Gauge& gauge) = 0;

};

