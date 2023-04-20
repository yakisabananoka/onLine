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

    virtual void Init(void);                                                                                    //初期化
    virtual void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;        //更新
    virtual void ConfirmUpdate(double delta, const Stage& stage)override;                                       //アップデートの確定
    virtual void Draw(void) = 0;                                                                                //描画

    virtual bool Motion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage) = 0;            //動き
    virtual bool DeathMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage);           //死んだときの動き
    virtual bool DamagedMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage);         //ダメージを受けたときの動き
    virtual bool IsTouchTrampoline(void) { return true; }                                                       //トランポリンに触れるか

    bool IsUnit(void)const override                             //Unitクラスか
    {
        return true;
    }

    const State& GetState(void)const;                           //ステートの取得
    void SetState(State state);                                 //ステートの設定

    const Circle& GetColCircle(void)const;                      //円の当たり判定の取得

    void AddMoveVec(Vector2Dbl vec);                            //移動ベクトルの加算
    void AddCorrectVec(Vector2Dbl vec);                         //補正ベクトルの加算

    Vector2Dbl GetMovedPos(double delta);                       //移動後の位置の取得

    void AddDamagedPnt(int pnt, const Vector2Dbl& pos);         //ダメージの加算
    void SetInvincible(double time);                            //透明化の設定

protected:
    void InitBeforeMove(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage);        //動く前の初期化
    void CorrectMove(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage);           //移動ベクトルの補正

    void CorrectPos(const Stage& stage);                                                                //位置の補正

    Vector2Dbl CheckMove(const ColPtr& col, Vector2Dbl moveVec)const;                                   //個別のコリジョンとの当たり判定
    Vector2Dbl CheckMove(const ColPtrList& colList, Vector2Dbl moveVec)const;                           //ステージの固定オブジェクトとの当たり判定
    Vector2Dbl CheckMove(const ObjList& objList, Vector2Dbl moveVec)const;                              //Objとの当たり判定
    Vector2Dbl CheckMove(LineCtrl& lineCtrl, int& intoLineCnt, Vector2Dbl moveVec)const;                //線との当たり判定

    bool CheckRayLine(Raycast::Ray ray, LineCtrl& lineCtrl)const;                                       //線に対してレイを飛ばす

    State UpdateState(ObjList& objList, LineCtrl& lineCtrl, const Stage& stage, Vector2Dbl checkVec)const;                                      //ステートの更新
    State UpdateState(LineCtrl& lineCtrl, const Vector2Dbl& colCorrect, const Vector2Dbl& objCorrect, const Vector2Dbl& lineCorrect)const;      //ステートの更新

    Raycast raycast_;               //レイキャスト
    Vector2Dbl moveVec_;            //移動ベクトル
    Vector2Dbl correctVec_;         //補正ベクトル
    Vector2Dbl nextMoveVec_;        //次の移動ベクトル
    bool jumpFlg_;                  //ジャンプできるか否か
    const Vector2Dbl groundRayMaxVec_;              //床チェックのレイの最大ベクトル
    const Vector2Dbl wallRayMaxVec_;                //壁チェックのレイの最大ベクトル
    int intoLineCnt_;                               //めり込み数

    double gravity_;                                //重力の値

    std::unique_ptr<double> boundThre_;             //跳ね閾値
    std::unique_ptr<double> boundCoeff_;            //跳ね係数

    double maxSpeed_;               //最大速度

    State state_;                   //現在のステート
    State stateOld_;                //前フレームのステート

    double time_;                   //経過時間
    double stateTime_;              //現在ステートの経過時間

    Circle colCircle_;              //当たり判定の円

    int lifePnt_;                   //体力
    const int defLifePnt_;          //体力の初期値

    std::unique_ptr<Vector2Dbl> damagedPos_;        //ダメージを受けた位置

    std::unique_ptr<double> invicibleTime_;         //透明時間

};

