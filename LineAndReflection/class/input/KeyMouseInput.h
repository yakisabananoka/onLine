#pragma once
#include <array>
#include "Controller.h"

class KeyMouseInput :
    public Controller
{
public:
    KeyMouseInput();
    ~KeyMouseInput();

    void Update(void)override;      //�X�V

    CntType GetCntType(void)const override { return CntType::KEY_MOUSE; };      //�R���g���[���[�̎�ނ̎擾

    unsigned int GetID(InputID inputId)const override;              //�e�[�u���̎��l�̎擾
    void SetID(InputID inputId, unsigned int keyId)override;        //�e�[�u���̎��l�̐ݒ�

private:
    std::map<InputID, unsigned int> keyTbl_;        //�L�[�{�[�h�p�̃e�[�u��
    std::map<InputID, unsigned int> mouseTbl_;      //�}�E�X�p�̃e�[�u��

    std::array<char, 256U> keyData_;        //�L�[�f�[�^�̎擾�p
    int mouseData_;                         //�}�E�X�f�[�^�̎擾�p
};

