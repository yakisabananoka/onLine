#pragma once
#include <memory>
#include "../scene/SceneID.h"
#include "Obj.h"
#include "ObjType.h"

class Controller;

class Door :
    public Obj
{
public:
    enum class State
    {
        None,
        OnDoor
    };

    Door(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id, std::string nextMapPath, bool useFadeImage, std::string fadeImagePath, bool useThumb, std::string thumbImagePath);
    ~Door();

    void Init(void) override;
    void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void Draw(void) override;

    ObjType GetObjType(void)const override
    {
        return ObjType::DOOR;
    }

private:
    std::shared_ptr<Controller> controller_;        //コントローラー
    State state_;                                   //ステート

    Vector2Dbl size_;                               //サイズ
    std::string nextMapPath_;                       //次のマップのファイルパス

    bool useFadeImage_;                             //フェードをするか
    std::string fadeImagePath_;                     //フェード用のイメージファイルのパス

    bool useThumb_;                                 //サムネイルを使うか
    std::string thumbImagePath_;                    //サムネイル画像のファイルパス
};
