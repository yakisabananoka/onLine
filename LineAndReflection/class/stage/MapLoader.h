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

	bool LoadMap(std::string path);								//�}�b�v�ǂݍ���

	const unsigned int& GetLayerSize(void)const;				//���C���[�T�C�Y�擾
	const Vector2& GetWorldArea(void)const;						//�}�b�v�̃T�C�Y�̎擾
	const Vector2& GetViewArea(void)const;						//�\������G���A�̃T�C�Y���擾
	const Vector2& GetTileSize(void)const;						//�^�C���T�C�Y�̎擾

	const MapData& GetMapData(void)const;						//�}�b�v�f�[�^�̎擾
	int GetMapData(std::string layer, Vector2 pos)const;		//pos�͍��W
	int GetMapData(std::string layer, int x, int y)const;		//x,y�̓}�X��

	const ColPtrList& GetColLsit(void)const;					//�����蔻�胊�X�g�̎擾

	const JsonList& GetObjInfoList(void)const;					//�������ׂ��I�u�W�F�N�g�̏��̃��X�g

	const std::string& GetBackgroundPath(void)const;			//�w�i�̃p�X�̎擾

	const std::string& GetBGM(void)const;						//BGM�̎擾

	const Tileset& GetTileset(unsigned int num);				//�Ώۂ̃^�C���Z�b�g�̎擾

	const Color& GetBGColor(void)const;

	const Color& GetStageColor(void)const;
	const Color& GetGrassColor(void)const;

	const Color& GetParticleColor(void)const;
	const Color& GetLineColor(void)const;
	const std::string& GetLineType(void)const;

private:
	bool CheckTiledVersion(std::string version);				//�o�[�W�����`�F�b�N�p
	bool LoadTileset(std::string path,Tileset& tileset);		//�^�C���Z�b�g
	bool SetMap(void);											//�}�b�v�̐ݒu

	std::unordered_map<std::string, int> version_;				//���e����o�[�W�������i�[

	//�}�b�v
	rapidjson::Document mapDoc_;							//JSON�`���̃}�b�v���
	unsigned int layerSize_;								//���C���[�̐�
	Vector2 worldArea_;										//���[���h�̃T�C�Y
	Vector2 viewArea_;										//�\������G���A�̃T�C�Y
	Vector2 tileSize_;										//�^�C���̃T�C�Y
	MapData mapData_;										//�}�b�v�̃f�[�^
	ColPtrList colList_;									//�����蔻�胊�X�g
	JsonList objInfoList_;									//�������ׂ��I�u�W�F�N�g�̏��̃|�C���^�̃��X�g
	std::string backgroundPath_;							//�w�i�̃p�X
	std::string bgmPath_;									//BGM�̃p�X
	
	Color bgColor_;

	Color stageColor_;
	Color grassColor_;

	Color particleColor_;
	Color lineColor_;
	std::string lineType_;

	//�^�C���Z�b�g
	std::vector<Tileset> tilesetList_;						//�^�C���Z�b�g�̔z��

	void operator=(const MapLoader&) = delete;
};

