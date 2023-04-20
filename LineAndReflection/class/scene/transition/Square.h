#pragma once
#include "TransitionScene.h"
class Square :
	public TransitionScene
{
public:
	Square(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::SquareArgs> args);
	~Square();

private:
	void DrawOwnScreen(void) override;		//TransitionScene�N���X�ɖ����Ă�����
	bool UpdateTransition(double delta) override;

	void DrawCloseTile(int x, int y, int count);	//X��Y�̓}�X�ڐ�
	void DrawOpenTile(int x, int y, int count);		//X��Y�̓}�X�ڐ�

	int count_;					//�J�E���g�l1
	int count2_;				//�J�E���g�l2

	Vector2 chipSize_;			//�`�b�v��̃T�C�Y
	Vector2 viewArea_;			//�����͈�

	const int tTime;
	int nextScr_;		//���̃X�N���[��
};

