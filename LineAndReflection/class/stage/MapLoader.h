#pragma once
#include <functional>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include "Tileset.h"
#include "../collision/usingCollision.h"
#include "../common/Color.h"
#include "../common/Vector2.h"
#include "../../parser/rapidjson/document.h"

using MapData = std::map<std::string, std::vector<int>>;
using JsonList = std::vector<const rapidjson::Value*>;

class MapLoader
{
public:
	MapLoader();
	~MapLoader();

	bool LoadMap(std::string path);								//マップ読み込み

	const unsigned int& GetLayerSize(void)const;				//レイヤーサイズ取得
	const Vector2& GetWorldArea(void)const;						//マップのサイズの取得
	const Vector2& GetViewArea(void)const;						//表示するエリアのサイズを取得
	const Vector2& GetTileSize(void)const;						//タイルサイズの取得

	const MapData& GetMapData(void)const;						//マップデータの取得
	int GetMapData(std::string layer, Vector2 pos)const;		//posは座標
	int GetMapData(std::string layer, int x, int y)const;		//x,yはマス目

	const ColPtrList& GetColLsit(void)const;					//当たり判定リストの取得

	const JsonList& GetObjInfoList(void)const;					//生成すべきオブジェクトの情報のリスト

	const std::string& GetBackgroundPath(void)const;			//背景のパスの取得

	const std::string& GetBGM(void)const;						//BGMの取得

	const Tileset& GetTileset(unsigned int num);				//対象のタイルセットの取得

	const Color& GetBGColor(void)const;

	const Color& GetStageColor(void)const;
	const Color& GetGrassColor(void)const;

	const Color& GetParticleColor(void)const;
	const Color& GetLineColor(void)const;
	const std::string& GetLineType(void)const;

private:
	bool CheckTiledVersion(std::string version);				//バージョンチェック用
	bool LoadTileset(std::string path,Tileset& tileset);		//タイルセット
	bool SetMap(void);											//マップの設置

	std::unordered_map<std::string, int> version_;				//許容するバージョンを格納

	//マップ
	rapidjson::Document mapDoc_;							//JSON形式のマップ情報
	unsigned int layerSize_;								//レイヤーの数
	Vector2 worldArea_;										//ワールドのサイズ
	Vector2 viewArea_;										//表示するエリアのサイズ
	Vector2 tileSize_;										//タイルのサイズ
	MapData mapData_;										//マップのデータ
	ColPtrList colList_;									//当たり判定リスト
	JsonList objInfoList_;									//生成すべきオブジェクトの情報のポインタのリスト
	std::string backgroundPath_;							//背景のパス
	std::string bgmPath_;									//BGMのパス
	
	Color bgColor_;

	Color stageColor_;
	Color grassColor_;

	Color particleColor_;
	Color lineColor_;
	std::string lineType_;

	//タイルセット
	std::vector<Tileset> tilesetList_;						//タイルセットの配列

	void operator=(const MapLoader&) = delete;
};

