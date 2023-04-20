#pragma once
#include <string>
#include "Obj.h"
#include "ObjType.h"

class ImageObj :
    public Obj
{
public:
    ImageObj(std::weak_ptr<Camera> camera, Vector2Dbl pos, std::string path, double deg, double mag, int id);
    ~ImageObj();

    void Init(void) override;
    void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void Draw(void) override;

    ObjType GetObjType(void)const override
    {
        return ObjType::IMAGE_OBJ;
    }

private:
    std::string path_;  //�t�@�C���p�X

    double rad_;        //��]��
    double mag_;        //�g�嗦
};

