#include "ObjGenerator.h"
#include "../Obj.h"
#include "../ObjType.h"
#include "Generators.h"

ObjGenerator::ObjGenerator(std::weak_ptr<Camera> camera) :
	camera_(camera)
{
	generatrorsMap_.try_emplace("player", ObjGenerators::PlayerGenerator());
	generatrorsMap_.try_emplace("goal", ObjGenerators::GoalGenerator());
	generatrorsMap_.try_emplace("lineHolder", ObjGenerators::LineHolderGenerator());
	generatrorsMap_.try_emplace("door", ObjGenerators::DoorGenerator());
	generatrorsMap_.try_emplace("block", ObjGenerators::BlockGenerator());
	generatrorsMap_.try_emplace("boundEnemy", ObjGenerators::BoundEnemyGenerator());
	generatrorsMap_.try_emplace("coin", ObjGenerators::CoinGenerator());
	generatrorsMap_.try_emplace("coinCtrl", ObjGenerators::CoinCtrlGenerator());
	generatrorsMap_.try_emplace("savePoint", ObjGenerators::SavePointGenerator());
	generatrorsMap_.try_emplace("imageObj", ObjGenerators::ImageObjGenerator());
	generatrorsMap_.try_emplace("rock", ObjGenerators::RockGenerator());
	generatrorsMap_.try_emplace("rockSetter", ObjGenerators::RockSetterGenerator());
	generatrorsMap_.try_emplace("thorn", ObjGenerators::ThornGenerator());
	generatrorsMap_.try_emplace("runEnemy", ObjGenerators::RunEnemyGenerator());
}

ObjGenerator::~ObjGenerator()
{
}

ObjPtr ObjGenerator::Generate(std::string type, const rapidjson::Value& rjObj)
{
	return generatrorsMap_[type](camera_, rjObj);
}
