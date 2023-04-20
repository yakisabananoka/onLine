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

//Obj�n�����p�̊֐��I�u�W�F�N�g
namespace ObjGenerators
{
	//�v���[���[�p
	struct PlayerGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera,const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<Player>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};

	//�S�[���p
	struct GoalGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<Goal>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};

	//���C���z���_�[�p
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

	//�h�A�p
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

	//�u���b�N�p
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

	//���˂�G�p
	struct BoundEnemyGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<BoundEnemy>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};

	//�R�C���p
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

	//�R�C���̃R���g���[���p
	struct CoinCtrlGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<CoinCtrl>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};

	//�Z�[�u�|�C���g�p
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

	//�摜�I�u�W�F�N�g�p
	struct ImageObjGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);
			auto pos = Vector2Dbl(search("x").GetDouble(), search("y").GetDouble());
			return std::make_shared<ImageObj>(camera, pos, search("path").GetString(), search("deg").GetDouble(), search("mag").GetDouble(), search("id").GetInt());
		}
	};

	//��p
	struct RockGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);
			auto pos = Vector2Dbl(search("x").GetDouble(), search("y").GetDouble());
			return std::make_shared<Rock>(camera, pos, search("id").GetInt());
		}
	};

	//�␶���p
	struct RockSetterGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);
			auto pos = Vector2Dbl(search("x").GetDouble(), search("y").GetDouble());
			return std::make_shared<RockSetter>(camera, pos, search("minX").GetDouble(), search("maxX").GetDouble(), search("genTime").GetDouble(), search("id").GetInt());
		}
	};

	//�g�Q�p
	struct ThornGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);
			return std::make_shared<Thorn>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};

	//������G�p
	struct RunEnemyGenerator
	{
		ObjPtr operator()(std::weak_ptr<Camera> camera, const rapidjson::Value& rjObj)
		{
			auto search = PropertySearch(rjObj);

			return std::make_shared<RunEnemy>(camera, Vector2Dbl(search("x").GetDouble(), search("y").GetDouble()), search("id").GetInt());
		}
	};


}
