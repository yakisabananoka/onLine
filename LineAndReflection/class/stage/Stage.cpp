#include "../scene/SceneMng.h"
#include "Stage.h"
#include "../obj/generator/ObjGenerator.h"
#include "../scene/Camera.h"
#include "../obj/unit/Player.h"
#include "../common/ImageMng.h"
#include "../common/Color.h"

//Stageクラスの定数
namespace stage_const
{
	
}

Stage::Stage(std::string path, std::weak_ptr<Camera> camera) :
	camera_(camera)
{
	mapLoader_.LoadMap(path);

	Init();
}

Stage::~Stage()
{
}

void Stage::Init(void)
{
}

void Stage::Update(double delta)
{
	cntTime_ += delta;
}

void Stage::Draw(void)
{
	//各種値の参照取得
	const Vector2& tileSize = mapLoader_.GetTileSize();
	const Vector2& viewArea = mapLoader_.GetViewArea();
	const Vector2& worldArea = mapLoader_.GetWorldArea();

	Vector2 camOffset;
	
	if (!camera_.expired())
	{
		//カメラが存在している場合描画用のオフセットをセットする
		camOffset = static_cast<Vector2>(camera_.lock()->GetDrawOffset());
	}

	//背景描画
	Rect camRange;
	camRange.pos = static_cast<Vector2Dbl>(-camOffset);
	camRange.size = static_cast<Vector2Dbl>(lpSceneMng.GetWindowSize());

	int imageHandle = lpImageMng.GetID(mapLoader_.GetBackgroundPath())[0];
	Vector2 bgSize = lpImageMng.GetSize(mapLoader_.GetBackgroundPath());
	Vector2 worldSize = worldArea * tileSize;

	Rect bgRect;
	bgRect.size = static_cast<Vector2Dbl>(bgSize);

	if (bgSize != Vector2())
	{
		for (int y = 0; y < worldSize.y; y += bgSize.y)
		{
			for (int x = 0; x < worldSize.x; x += bgSize.x)
			{
				bgRect.pos = Vector2Dbl(static_cast<double>(x), static_cast<double>(y));
				if (!bgRect.CheckHit(camRange))
				{
					continue;
				}

				DrawGraph(camOffset.x + x, camOffset.y + y, imageHandle, true);
			}
		}
	}
	
		//DrawGraph(0, 0, lpImageMng.GetID(mapLoader_.GetBackgroundPath())[0], true);

	auto offsetTile = static_cast<Vector2>(-camOffset / tileSize);

	//マップチップの描画
	Color origin;
	GetDrawBright(&origin.r, &origin.g, &origin.b);

	const auto& stageColor = mapLoader_.GetStageColor();
	const auto& grassColor = mapLoader_.GetGrassColor();

	for (const auto& layer : mapLoader_.GetMapData())
	{
		for (int y = offsetTile.y; y < std::min(offsetTile.y + viewArea.y + 1, worldArea.y); y++)
		{
			for (int x = offsetTile.x; x < std::min(offsetTile.x + viewArea.x + 1, worldArea.x); x++)
			{
				int point = mapLoader_.GetMapData(layer.first, x, y);

				if (!point)
				{
					continue;
				}

				const auto& tileset = mapLoader_.GetTileset(point);
				if (point >= 0)
				{	
					SetDrawBright(stageColor.r, stageColor.g, stageColor.b);
					DrawGraph(
						camOffset.x + tileSize.x * x,
						camOffset.y + tileSize.y * y,
						lpImageMng.GetID(tileset.keyName)[static_cast<size_t>(point) - tileset.firstGID_], true
					);

					SetUseMaskScreenFlag(true);
					DrawMask(
						camOffset.x + tileSize.x * x,
						camOffset.y + tileSize.y * y,
						lpImageMng.GetMaskID(tileset.keyName)[static_cast<size_t>(point) - tileset.firstGID_], DX_MASKTRANS_NONE
					);

					SetDrawBright(grassColor.r, grassColor.g, grassColor.b);
					DrawGraph(
						camOffset.x + tileSize.x * x,
						camOffset.y + tileSize.y * y,
						lpImageMng.GetID(tileset.keyName)[static_cast<size_t>(point) - tileset.firstGID_], true
					);
					SetUseMaskScreenFlag(false);
				}
			}
		}
	}

	SetDrawBright(origin.r, origin.g, origin.b);
	
}

void Stage::SetObj(ObjList& objList)
{
	//初期化
	objList.clear();

	const auto& objInfoList = mapLoader_.GetObjInfoList();

	//オブジェクトの生成
	ObjGenerator objGenerator(camera_);
	for (const auto& objInfo : objInfoList)
	{
		objList.emplace_back(objGenerator.Generate((*objInfo)["name"].GetString(), *objInfo));
	}

}
