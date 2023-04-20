#include "LineGenerator.h"
#include "Generators.h"

LineGenerator::LineGenerator(std::weak_ptr<Camera> camera) :
	camera_(camera)
{
	genMap_.try_emplace("correct", LineGenerators::CorrectLineGenerator());
	genMap_.try_emplace("free", LineGenerators::FreeLineGenerator());
	genMap_.try_emplace("trampoline", LineGenerators::TrampolineGenerator());
	genMap_.try_emplace("conveyor", LineGenerators::ConveyorGenerator());
}

LineGenerator::~LineGenerator()
{
}

LinePtr LineGenerator::Generate(std::string lineType, unsigned int color)const
{
	if (!genMap_.count(lineType))
	{
		return nullptr;
	}

	return genMap_.at(lineType)(camera_, color);
}
