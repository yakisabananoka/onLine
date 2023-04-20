#pragma once
#include <memory>
#include <random>
#include <vector>
#include "usingEffectObj.h"
#include "../common/Vector2.h"

class Camera;

class ItemEffect
{
public:
	ItemEffect(std::weak_ptr<Camera> camera, Vector2Dbl pos);
	~ItemEffect();

	void Update(double delta);				//�X�V
	void Draw(void);						//�`��

	bool IsEnd(void)const;					//�I�����Ă��邩

private:
	std::weak_ptr<Camera> camera_;			//�J����

	std::random_device seed_;				//�V�[�h�l�𐶐�
	std::mt19937 randomGen_;				//���������p

	std::uniform_real_distribution<> outVecXRange_;		//X�͈̔�
	std::uniform_real_distribution<> outVecYRange_;		//Y�͈̔�

	EffPtrVec effList_;			//�G�t�F�N�g�̃��X�g

	Vector2Dbl pos_;			//��ʒu
};

