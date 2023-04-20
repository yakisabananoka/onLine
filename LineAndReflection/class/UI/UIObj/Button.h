#pragma once
#include <memory>
#include <functional>
#include <list>
#include <unordered_map>
#include <string>
#include "BaseUI.h"
#include "ButtonCommand/ButtonCommand.h"

class Controller;

class Button :
    public BaseUI
{
public:
	enum class State
	{
		JustOn,				//�������u��
		JustOff,			//�������u��
		NowOn,				//������Ă���
		NowOff,				//�����Ă���
		NowEnter,			//����Ƀ}�E�X�������Ă���
		NowLeave,			//����Ƀ}�E�X�������Ă��Ȃ�
		JustEnter,			//����Ƀ}�E�X���������u��
		JustLeave			//���肩��}�E�X���o���u��
	};

	Button(Vector2Dbl pos, const std::string& imageKey, bool alphaCheck = true);
	~Button();

	virtual void Init(void)override;
	virtual void Update(double delta)override;
	virtual void SpotUpdate(std::shared_ptr<Controller> controller)override;		//���C���������Ă���ꍇ�Ɏ��s���鏈��
	virtual void Draw(void)override;

	virtual bool IsIntoMousePos(const Vector2Dbl& mousePos)override;				//�}�E�X�̍��W�Ƃ̓����蔻��`�F�b�N

	virtual UIType GetUIType(void)override
	{
		return UIType::Button;
	}

	virtual void SetCommand(State state, ButtonCommandPtr command);					//���ꂼ��̏�Ԃ̎��Ɏ��s����R�}���h�̐ݒ�

	virtual void SetCC(Vector2Dbl pos);												//���S�ʒu�̐ݒ�
	
	virtual void SetImageKey(std::string imageKey);									//�摜�̃L�[�̐ݒ�

private:
	void InitImage(void);													//�����ʒu

	bool alphaCheck_;

	std::shared_ptr<Controller> controller_;

	std::string imageKey_;

	std::unordered_map<State, BCPtrList> commandMap_;
	
	State oldEnterState_;
};

