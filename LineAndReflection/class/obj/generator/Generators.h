#pragma once
#include <memory>
#include "ObjGenerator.h"
#include "../unit/Player.h"
#include "../unit/BoundEnemy.h"
#include "../Goal.h"
#include "../LineHolder.h"
#include "../Door.h"
#include "../Block.h"
#include "../Coin.h"
#include "../CoinCtrl.h"
#include "../SavePoint.h"
#include "../ImageObj.h"
#include "../unit/Rock.h"
#include "../RockSetter.h"
#include "../unit/Thorn.h"
#include "../unit/RunEnemy.h"
#include "../../common/PropertySearch.h"
#include "../../common/Vector2.h"

//Obj系生成用の関数オブジェクト
namespace ObjGenerators
{
	//プレーヤー用
	struct PlayerGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera,const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<Player>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};

	//ゴール用
	struct GoalGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<Goal>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};

	//ラインホルダー用
	struct LineHolderGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<LineHolder>(
				camera,
				Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()),
				Vector2Dbl(search("x1").GetDouble(), search("y1").GetDouble()),
				search("id").GetInt(),
				search("lineType").GetString()
				);
		}
	};

	//ドア用
	struct DoorGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<Door>(
				camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()),
				search("id").GetInt(), search("nextMapPath").GetString(),
				search("useFadeImage").GetBool(), search("fadeImagePath").GetString(),
				search("useThumb").GetBool(), search("thumbImagePath").GetString()
				);
		}
	};

	//ブロック用
	struct BlockGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			Rect range;
			range.pos = Vector2Dbl(search("x").GetDouble(), search("y").GetDouble());
			range.size = Vector2Dbl(search("width").GetDouble(), search("height").GetDouble());

			return std::make_shared<Block>(camera, range, search("id").GetInt());
		}
	};

	//跳ねる敵用
	struct BoundEnemyGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<BoundEnemy>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};

	//コイン用
	struct CoinGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			Rect range;
			range.pos = Vector2Dbl(search("x").GetDouble(), search("y").GetDouble());
			range.size = Vector2Dbl(search("width").GetDouble(), search("height").GetDouble());

			return std::make_shared<Coin>(camera, range, search("id").GetInt(), search("chipId").GetInt());
		}
	};

	//コインのコントロール用
	struct CoinCtrlGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<CoinCtrl>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};

	//セーブポイント用
	struct SavePointGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			Rect range;
			range.pos = Vector2Dbl(search("x").GetDouble(), search("y").GetDouble());
			range.size = Vector2Dbl(search("width").GetDouble(), search("height").GetDouble());

			return std::make_shared<SavePoint>(camera, range, search("id").GetInt());
		}
	};

	//画像オブジェクト用
	struct ImageObjGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);
			auto pos = Vector2Dbl(search("x").GetDouble(), search("y").GetDouble());
			return std::make_shared<ImageObj>(camera, pos, search("path").GetString(), search("deg").GetDouble(), search("mag").GetDouble(), search("id").GetInt());
		}
	};

	//岩用
	struct RockGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);
			auto pos = Vector2Dbl(search("x").GetDouble(), search("y").GetDouble());
			return std::make_shared<Rock>(camera, pos, search("id").GetInt());
		}
	};

	//岩生成用
	struct RockSetterGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);
			auto pos = Vector2Dbl(search("x").GetDouble(), search("y").GetDouble());
			return std::make_shared<RockSetter>(camera, pos, search("minX").GetDouble(), search("maxX").GetDouble(), search("genTime").GetDouble(), search("id").GetInt());
		}
	};

	//トゲ用
	struct ThornGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);
			return std::make_shared<Thorn>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};

	//走り回る敵用
	struct RunEnemyGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<RunEnemy>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};


}
