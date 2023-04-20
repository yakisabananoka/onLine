#pragma once
#include "../Obj.h"
#include "../../collision/usingCollision.h"
#include "../../common/Raycast.h"
#include "../../common/shape/Circle.h"

class Unit :
    public Obj
{
public:
    enum class State
    {
        TouchCeiling,
        TouchFloor,
        Sandwiched,
        InAir,
        Damaged,
        Death
    };

    Unit(std::weak_ptr<Camera> camera, const Vector2Dbl& pos, const double& radius, const int& id, const double& gravity, const double& maxSpeed, int lifePnt = 1);
    ~Unit();

    virtual void Init(void);                                                                                    //������
    virtual void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;        //�X�V
    virtual void ConfirmUpdate(double delta, const Stage& stage)override;                                       //�A�b�v�f�[�g�̊m��
    virtual void Draw(void) = 0;                                                                                //�`��

    virtual bool Motion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage) = 0;            //����
    virtual bool DeathMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage);           //���񂾂Ƃ��̓���
    virtual bool DamagedMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage);         //�_���[�W���󂯂��Ƃ��̓���
    virtual bool IsTouchTrampoline(void) { return true; }                                                       //�g�����|�����ɐG��邩

    bool IsUnit(void)const override                             //Unit�N���X��
    {
        return true;
    }

    const State& GetState(void)const;                           //�X�e�[�g�̎擾
    void SetState(State state);                                 //�X�e�[�g�̐ݒ�

    const Circle& GetColCircle(void)const;                      //�~�̓����蔻��̎擾

    void AddMoveVec(Vector2Dbl vec);                            //�ړ��x�N�g���̉��Z
    void AddCorrectVec(Vector2Dbl vec);                         //�␳�x�N�g���̉��Z

    Vector2Dbl GetMovedPos(double delta);                       //�ړ���̈ʒu�̎擾

    void AddDamagedPnt(int pnt, const Vector2Dbl& pos);         //�_���[�W�̉��Z
    void SetInvincible(double time);                            //�������̐ݒ�

protected:
    void InitBeforeMove(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage);        //�����O�̏�����
    void CorrectMove(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage);           //�ړ��x�N�g���̕␳

    void CorrectPos(const Stage& stage);                                                                //�ʒu�̕␳

    Vector2Dbl CheckMove(const ColPtr& col, Vector2Dbl moveVec)const;                                   //�ʂ̃R���W�����Ƃ̓����蔻��
    Vector2Dbl CheckMove(const ColPtrList& colList, Vector2Dbl moveVec)const;                           //�X�e�[�W�̌Œ�I�u�W�F�N�g�Ƃ̓����蔻��
    Vector2Dbl CheckMove(const ObjList& objList, Vector2Dbl moveVec)const;                              //Obj�Ƃ̓����蔻��
    Vector2Dbl CheckMove(LineCtrl& lineCtrl, int& intoLineCnt, Vector2Dbl moveVec)const;                //���Ƃ̓����蔻��

    bool CheckRayLine(Raycast::Ray ray, LineCtrl& lineCtrl)const;                                       //���ɑ΂��ă��C���΂�

    State UpdateState(ObjList& objList, LineCtrl& lineCtrl, const Stage& stage, Vector2Dbl checkVec)const;                                      //�X�e�[�g�̍X�V
    State UpdateState(LineCtrl& lineCtrl, const Vector2Dbl& colCorrect, const Vector2Dbl& objCorrect, const Vector2Dbl& lineCorrect)const;      //�X�e�[�g�̍X�V

    Raycast raycast_;               //���C�L���X�g
    Vector2Dbl moveVec_;            //�ړ��x�N�g��
    Vector2Dbl correctVec_;         //�␳�x�N�g��
    Vector2Dbl nextMoveVec_;        //���̈ړ��x�N�g��
    bool jumpFlg_;                  //�W�����v�ł��邩�ۂ�
    const Vector2Dbl groundRayMaxVec_;              //���`�F�b�N�̃��C�̍ő�x�N�g��
    const Vector2Dbl wallRayMaxVec_;                //�ǃ`�F�b�N�̃��C�̍ő�x�N�g��
    int intoLineCnt_;                               //�߂荞�ݐ�

    double gravity_;                                //�d�͂̒l

    std::unique_ptr<double> boundThre_;             //����臒l
    std::unique_ptr<double> boundCoeff_;            //���ˌW��

    double maxSpeed_;               //�ő呬�x

    State state_;                   //���݂̃X�e�[�g
    State stateOld_;                //�O�t���[���̃X�e�[�g

    double time_;                   //�o�ߎ���
    double stateTime_;              //���݃X�e�[�g�̌o�ߎ���

    Circle colCircle_;              //�����蔻��̉~

    int lifePnt_;                   //�̗�
    const int defLifePnt_;          //�̗͂̏����l

    std::unique_ptr<Vector2Dbl> damagedPos_;        //�_���[�W���󂯂��ʒu

    std::unique_ptr<double> invicibleTime_;         //��������

};

