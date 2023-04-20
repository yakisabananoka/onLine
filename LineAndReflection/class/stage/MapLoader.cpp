#include <fstream>
#include "MapLoader.h"
#include "../scene/SceneMng.h"
#include "../collision/Collision.h"
#include "../collision/SetCollisionForRect.h"
#include "../common/ImageMng.h"
#include "../common/Utility.h"
#include "../common/PropertySearch.h"
#include "../../parser/rapidjson/istreamwrapper.h"
#include "../../_debug/_debugConOut.h"

namespace mapLoader_const
{
    constexpr char nowVersion[] = "1.7.2";
}

using namespace mapLoader_const;

MapLoader::MapLoader()
{
    layerSize_ = 0;
    version_[nowVersion] = 1;

    bgColor_ = 0xffffff;
    
    stageColor_ = 0xffffff;
    grassColor_ = 0xffffff;

    particleColor_ = 0xffffff;
    lineColor_ = 0xffffff;
}

MapLoader::~MapLoader()
{
}

bool MapLoader::LoadMap(std::string path)
{
    //�t�@�C���X�g���[���œǂݍ���
    std::ifstream ifs(path);

    //�p�[�X
    rapidjson::IStreamWrapper isw(ifs);
    mapDoc_.ParseStream(isw);

    //�o�[�W�����`�F�b�N
    if (!CheckTiledVersion(utility::ConvertUTF8ToSJIS()(mapDoc_["tiledversion"].GetString())))
    {
        return false;
    }

    Tileset tileset;
    const auto& tilesets = mapDoc_["tilesets"];

    for (auto itr = tilesets.Begin(); itr != tilesets.End(); ++itr)
    {
        const auto& tilesetJson = itr->GetObj();

        std::string source = utility::ConvertUTF8ToSJIS()(itr->GetObj()["source"].GetString());

        //�^�C���Z�b�g�̃��[�h
        if (!LoadTileset(path.substr(0, path.find_last_of("/") + 1) + source, tileset))
        {
            return false;
        }

        tileset.firstGID_ = tilesetJson["firstgid"].GetInt();

        tilesetList_.push_back(tileset);
    }

    std::sort(tilesetList_.begin(), tilesetList_.end(), [](const Tileset& tilesetA, const Tileset& tilesetB) {return tilesetA.firstGID_ < tilesetB.firstGID_; });

    //�e��l�̑��
    layerSize_ = mapDoc_["nextlayerid"].GetInt() - 1;
    worldArea_ = { mapDoc_["width"].GetInt(),mapDoc_["height"].GetInt() };
    tileSize_ = { mapDoc_["tilewidth"].GetInt(),mapDoc_["tileheight"].GetInt() };
    viewArea_ = lpSceneMng.GetWindowSize() / tileSize_;

    auto search = PropertySearch(mapDoc_);
    bgmPath_ = search("BGM").GetString();
    lineType_ = search("lineType").GetString();
    
    auto stoc = [&](std::string str) {
        std::string col = search(str).GetString();
        return Color(static_cast<unsigned int>(std::stoi(search(str).GetString(), nullptr, 16)));
    };

    bgColor_ = stoc("BGColor");

    stageColor_ = stoc("StageColor");
    grassColor_ = stoc("GrassColor");

    lineColor_ = stoc("LineColor");
    particleColor_ = stoc("ParticleColor");

    //�}�b�v�̃Z�b�g
    return SetMap();
}

const unsigned int& MapLoader::GetLayerSize(void)const
{
    return layerSize_;
}

const Vector2& MapLoader::GetWorldArea(void)const
{
    return worldArea_;
}

const Vector2& MapLoader::GetViewArea(void) const
{
    return viewArea_;
}

const Vector2& MapLoader::GetTileSize(void)const
{
    return tileSize_;
}

const MapData& MapLoader::GetMapData(void)const
{
    return mapData_;
}

int MapLoader::GetMapData(std::string layer, Vector2 pos)const
{
    return GetMapData(layer, pos.x / tileSize_.x, pos.y / tileSize_.y);
}

int MapLoader::GetMapData(std::string layer, int x, int y)const
{
    if (!mapData_.count(layer))
    {
        return -1;
    }

    int point = y * worldArea_.x + x;

    if (point < 0 || point > mapData_.at(layer).size())
    {
        return -1;
    }

    return mapData_.at(layer)[point];
}

const ColPtrList& MapLoader::GetColLsit(void)const
{
    return colList_;
}

const JsonList& MapLoader::GetObjInfoList(void)const
{
    return objInfoList_;
}

const std::string& MapLoader::GetBackgroundPath(void)const
{
    return backgroundPath_;
}

const std::string& MapLoader::GetBGM(void)const
{
    return bgmPath_;
}

const Tileset& MapLoader::GetTileset(unsigned int num)
{
    //������
    auto nowItr = tilesetList_.begin();
    auto nextItr = std::next(nowItr, 1);

    for (; nextItr != tilesetList_.end(); ++nowItr, ++nextItr)
    {
        if ((nowItr->firstGID_ <= num) && (num < nextItr->firstGID_))
        {
            return *nowItr;
        }
    }

    return tilesetList_.back();
}

const Color& MapLoader::GetBGColor(void) const
{
    return bgColor_;
}

const Color& MapLoader::GetStageColor(void) const
{
    return stageColor_;
}

const Color& MapLoader::GetGrassColor(void) const
{
    return grassColor_;
}

const Color& MapLoader::GetParticleColor(void) const
{
    return particleColor_;
}

const Color& MapLoader::GetLineColor(void) const
{
    return lineColor_;
}

const std::string& MapLoader::GetLineType(void) const
{
    return lineType_;
}

bool MapLoader::CheckTiledVersion(std::string version)
{
    if (!version_.count(version))
    {
        TRACE("Tiled�̔�Ή��o�[�W����\n");
        return false;
    }
    if (!version_[version])
    {
        TRACE("Tiled�̔�Ή��o�[�W����\n");
        return false;
    }

    TRACE("Tiled�̑Ή��o�[�W����\n");

    return true;
}

bool MapLoader::LoadTileset(std::string path, Tileset& tileset)
{
    //�t�@�C���X�g���[���œǂݍ���
    std::ifstream ifs(path);

    //�p�[�X
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document tilesetDoc;
    tilesetDoc.ParseStream(isw);

    //�o�[�W�����`�F�b�N
    if (!CheckTiledVersion(utility::ConvertUTF8ToSJIS()(tilesetDoc["tiledversion"].GetString())))
    {
        return false;
    }

    //�^�C���Z�b�g�̉摜�̃p�X
    std::string source = utility::ConvertUTF8ToSJIS()(tilesetDoc["image"].GetString()).substr(3);
    
    bool result = true;
    const auto& value = PropertySearch(tilesetDoc)("mask", &result);
    std::unique_ptr<std::string> maskSource;
    if (result)
    {
        maskSource = std::make_unique<std::string>(utility::ConvertUTF8ToSJIS()(value.GetString()).substr(3));
    }

    tileset.keyName = utility::ConvertUTF8ToSJIS()(tilesetDoc["name"].GetString());

    //�摜�擾�̌v�Z�p�ϐ�
    int tileWidth = tilesetDoc["tilewidth"].GetInt();
    int tileHeight = tilesetDoc["tileheight"].GetInt();
    int tilecount = tilesetDoc["tilecount"].GetInt();
    int columns = tilesetDoc["columns"].GetInt();

    //�摜�擾
    lpImageMng.GetID("data/" + source, tileset.keyName, { tileWidth,tileHeight }, { columns,tilecount / columns });

    if (maskSource)
    {
        lpImageMng.GetMaskID("data/" + (*maskSource), tileset.keyName, { tileWidth,tileHeight }, { columns,tilecount / columns });
    }
    
    return true;
}

bool MapLoader::SetMap(void)
{
    //�^�C�����C���[�̃Z�b�g�p
    const auto setTileLayer = [&](const rapidjson::GenericObject<true,rapidjson::Value>& layerObj) {
        auto layer = mapData_.try_emplace(utility::ConvertUTF8ToSJIS()(layerObj["name"].GetString()));
        if (layer.second)
        {
            layer.first->second.resize(static_cast<size_t>(worldArea_.x) * worldArea_.y);
        }

        const auto& layerData = layerObj["data"];
        for (int i = 0; i < layer.first->second.size(); i++)
        {
            layer.first->second[i] = layerData[i].GetInt();
        }
    };

    //�I�u�W�F�N�g�̃Z�b�g�p
    const auto setObject = [&](const rapidjson::GenericObject<true, rapidjson::Value>& layerObj) {
        const auto& objects = layerObj["objects"];
        if (utility::ConvertUTF8ToSJIS()(layerObj["name"].GetString()) == "collision")
        {
            ColPtr colPtr;
            VertexPtr vertexPtr;
            IndexPtr indexPtr;
            Rect colRect;

            auto setVertexForRect = SetCollisionForRect::SetVertexPtr();
            auto setIndexForRect = SetCollisionForRect::SetIndexPtr();

            //�����蔻��̃Z�b�g
            for (auto colItr = objects.Begin(); colItr != objects.End(); ++colItr)
            {
                const auto& col = *colItr;

                if (col.HasMember("polygon"))
                {
                    //��`�ȊO�̑��p�`�̏ꍇ
                    const auto& properties = col["properties"];
                    const auto& polygon = col["polygon"];

                    vertexPtr = std::make_unique<VertexVec>();
                    vertexPtr->reserve(4);
                    indexPtr = std::make_unique<IndexVec>();
                    indexPtr->reserve(8);

                    Vector2Dbl basePos = { col["x"].GetDouble(),col["y"].GetDouble() };

                    //�v���p�e�B���画��p��`���擾
                    std::string proVal;
                    for (auto pItr = properties.Begin(); pItr != properties.End(); ++pItr)
                    {
                        const auto& proObj = pItr->GetObj();
                        proVal = proObj["name"].GetString();
                        if (proVal == "x")
                        {
                            colRect.pos.x = proObj["value"].GetDouble();
                        }
                        else if (proVal == "y")
                        {
                            colRect.pos.y = proObj["value"].GetDouble();
                        }
                        else if (proVal == "width")
                        {
                            colRect.size.x = proObj["value"].GetDouble();
                        }
                        else if (proVal == "height")
                        {
                            colRect.size.y = proObj["value"].GetDouble();
                        }
                    }

                    //���_���擾
                    int index = 0;
                    for (auto vItr = polygon.Begin(); vItr != polygon.End(); ++vItr)
                    {
                        const auto& ver = vItr->GetObj();
                        vertexPtr->emplace_back(Vector2Dbl(basePos.x + ver["x"].GetDouble(), basePos.y + ver["y"].GetDouble()));

                        if (index)
                        {
                            indexPtr->emplace_back(index - 1);
                            indexPtr->emplace_back(index);
                        }

                        index++;
                    }

                    indexPtr->emplace_back(index - 1);
                    indexPtr->emplace_back(0);

                }
                else
                {
                    //��`�̏ꍇ

                    colRect.pos = { col["x"].GetDouble(),col["y"].GetDouble() };
                    colRect.size = { col["width"].GetDouble(),col["height"].GetDouble() };

                    vertexPtr = setVertexForRect(colRect);
                    indexPtr = setIndexForRect(colRect);
                }

                colPtr = std::make_unique<Collision>(colRect);

                colPtr->SetVertexPtr(std::move(vertexPtr));
                colPtr->SetIndexPtr(std::move(indexPtr));

                colList_.emplace_back(std::move(colPtr));
            }
        }
        else
        {
            for (auto objItr = objects.Begin(); objItr != objects.End(); ++objItr)
            {
                objInfoList_.emplace_back(objItr);
            }
        }

    };

    const auto setImage = [&](const rapidjson::GenericObject<true, rapidjson::Value>& layerObj) {
        backgroundPath_ = utility::ConvertUTF8ToSJIS()(layerObj["image"].GetString());
        backgroundPath_ = "data/" + backgroundPath_.substr(3);
        lpImageMng.GetID(backgroundPath_);
    };

    //���C���[�̃^�C�v�ɉ����������_�����Z�b�g
    const std::unordered_map<std::string, std::function<void(const rapidjson::GenericObject<true, rapidjson::Value>&)>> setLayer = {
        {"tilelayer",setTileLayer},
        {"objectgroup",setObject},
        {"imagelayer",setImage}
    };

    const auto& layers = mapDoc_["layers"];
    for (auto layerItr = layers.Begin(); layerItr != layers.End(); ++layerItr)
    {
        const auto& layerObj = layerItr->GetObj();

        //���C���[�̃^�C�v�擾
        std::string typeName = utility::ConvertUTF8ToSJIS()(layerObj["type"].GetString());

        //���݂��Ȃ��^�C�v�̂��̂̓X�L�b�v
        if (!setLayer.count(typeName))
        {
            continue;
        }

        //���C���[�̃^�C�v�ɉ����������_�������s
        setLayer.at(typeName)(layerObj);

        TRACE("%s���C���[�擾\n", layerObj["name"].GetString());

    }

    return true;
}
