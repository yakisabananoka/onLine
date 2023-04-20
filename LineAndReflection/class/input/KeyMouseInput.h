#pragma once
#include <array>
#include "Controller.h"

class KeyMouseInput :
    public Controller
{
public:
    KeyMouseInput();
    ~KeyMouseInput();

    void Update(void)override;      //更新

    CntType GetCntType(void)const override { return CntType::KEY_MOUSE; };      //コントローラーの種類の取得

    unsigned int GetID(InputID inputId)const override;              //テーブルの実値の取得
    void SetID(InputID inputId, unsigned int keyId)override;        //テーブルの実値の設定

private:
    std::map<InputID, unsigned int> keyTbl_;        //キーボード用のテーブル
    std::map<InputID, unsigned int> mouseTbl_;      //マウス用のテーブル

    std::array<char, 256U> keyData_;        //キーデータの取得用
    int mouseData_;                         //マウスデータの取得用
};

