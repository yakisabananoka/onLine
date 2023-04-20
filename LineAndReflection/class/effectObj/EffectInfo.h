#pragma once
#include <memory>
#include <string>
#include "effectCommand/EffectCommand.h"
#include "../common/Vector2.h"

struct Trans
{
	void Update(const double& delta)
	{
		speed += accele * delta;
	}
	double speed = 0.0;		//����
	double accele = 0.0;	//�����x
};

struct EffectInfo
{
	std::string imageKey;						//�摜�̃L�[
	Vector2Dbl pos;								//�ʒu
	Vector2Dbl vec;								//�ړ�����
	Trans move;									//�ړ���
	Trans rota;									//��]��
	Trans exAmount;								//�g���
	Trans blendAmount;							//�u�����h��
	double angle = 0.0;							//�p�x
	double mag = 1.0;							//�g�嗦
	double lifeTime = 0.0;						//��������
	int blendMode = 0;							//�u�����h���[�h
	double blend = 0.0;							//�u�����h�̃p�����[�^�[(int�ɕϊ�)
	int r = 255;								//��(0�`255)
	int g = 255;								//��(0�`255)
	int b = 255;								//��(0�`255)
	std::unique_ptr<EffectCommand> command;		//�R�}���h
};

