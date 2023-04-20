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
    std::shared_ptr<Controller> controller_;        //�R���g���[���[
    State state_;                                   //�X�e�[�g

    Vector2Dbl size_;                               //�T�C�Y
    std::string nextMapPath_;                       //���̃}�b�v�̃t�@�C���p�X

    bool useFadeImage_;                             //�t�F�[�h�����邩
    std::string fadeImagePath_;                     //�t�F�[�h�p�̃C���[�W�t�@�C���̃p�X

    bool useThumb_;                                 //�T���l�C�����g����
    std::string thumbImagePath_;                    //�T���l�C���摜�̃t�@�C���p�X
};
