#pragma once
#include <memory>
#include <random>
#include <DxLib.h>
#include "../common/shape/Rect.h"
#include "../common/Vector2.h"

class Obj;
class Stage;

class Camera
{
public:
	Camera();
	~Camera();

	void Update(double delta);
	void Draw(void);

	const Vector2Dbl& GetPos(void)const;													//�ʒu�̎擾
	void SetPos(Vector2Dbl pos);														//�ʒu�̐ݒ�
	
	Vector2Dbl GetDrawOffset(void)const;													//�`�掞�̃I�t�Z�b�g�l�̎擾

	bool SetStageAndTarget(std::weak_ptr<Stage> stage, std::weak_ptr<Obj> target);			//�X�e�[�W�̐ݒ�(��������ɐݒ�)
	bool SetTarget(std::weak_ptr<Obj> target);

	void SetShake(double time, double mag);
	bool IsShake(void)const;

private:
	bool Init(void);					//�������p�֐�
	bool InitArea(void);				//�ړ��̈�̏�����

	std::weak_ptr<Obj> target_;			//�����_
	std::weak_ptr<Stage> stage_;		//�X�e�[�W

	Vector2Dbl defPos_;					//�����ʒu
	Vector2Dbl pos_;					//�ʒu

	Rect antiMoveRect;					//�ړ��s�̈�
	
	std::random_device seed_;
	std::mt19937 randomGen_;
	std::uniform_real_distribution<> shakeRange_;

	std::unique_ptr<double> shakeTime_;	//�h��鎞��
	double shakeMag_;					//�h���傫��


};

