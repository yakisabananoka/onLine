#pragma once
#include <array>
#include <map>
#include "InputID.h"
#include "../common/Vector2.h"

//���͑��u�̎��
enum class CntType
{
	KEY_MOUSE,		//�L�[�{�[�h�ƃ}�E�X
	MAX
};

//�o�b�t�@��
enum class Trg
{
	NOW,		//����
	OLD,		//�O�t���[��
	MAX
};

using TrgBool = std::array<bool, static_cast<size_t>(Trg::MAX)>;
using CntData = std::map<InputID, TrgBool>;

class Controller
{
public:
	Controller();
	virtual ~Controller() {};

	virtual void Update(void) = 0;					//�X�V
	virtual CntType GetCntType(void)const = 0;		//�R���g���[���[�̎�ނ��擾

	//�R���g���[���[�̃f�[�^�擾
	const CntData& GetCntData(void)const
	{
		return cntData_;
	}

	//�ʒu�擾
	const Vector2Dbl& GetPos(void)const
	{
		return pos_;
	}

	//��]�ʎ擾
	const int& GetRotate(void)const
	{
		return rota_;
	}

	virtual unsigned int GetID(InputID inputId)const = 0;				//�L�[�e�[�u���ɐݒ肳��Ă�����l���擾
	virtual void SetID(InputID inputId, unsigned int keyId) = 0;		//���l���L�[�e�[�u���ɐݒ�

	bool NowOn(InputID inputID)const;		//���݉�����Ă��邩
	bool NowOff(InputID inputID)const;		//���ݗ���Ă��邩
	bool JustOn(InputID inputID)const;		//�����ꂽ�u��
	bool JustOff(InputID inputID)const;		//���ꂽ�u��

	void SetAcitive(bool flg);				//�A�N�e�B�u��Ԃ̐؂�ւ�
	
protected:
	CntData cntData_;		//������Ԃ̃f�[�^
	Vector2Dbl pos_;		//���݈ʒu

	int rota_;				//��]��

	bool activeFlg_;		//�L�����ۂ�
};

