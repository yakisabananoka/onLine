#pragma once
#include <memory>
#include <random>
#include <vector>
#include "usingEffectObj.h"

class Controller;

class MouseStalker
{
public:
	MouseStalker();
	~MouseStalker();

	void Update(void);		//�X�V
	void Draw(void);		//�`��

private:
	std::shared_ptr<Controller> controller_;		//�R���g���[���[

	std::random_device seed_;						//�V�[�h�l����
	std::mt19937 randomGen_;						//��������

	std::uniform_real_distribution<> rangeVecX_;		//X�͈̔�
	std::uniform_real_distribution<> rangeVecY_;		//Y�͈̔�
	std::uniform_real_distribution<> rangeShiftAngle_;	//�p�x�͈̔�

	EffPtrVec effList_;			//�G�t�F�N�g�̃��X�g

	Vector2Dbl oldMousePos;		//�O�t���[���̃}�E�X�̈ʒu

	Vector2Dbl mousePos_;		//���݂̃}�E�X�̈ʒu

};

