#pragma once
#include <string>
#include "generator/SceneGenerator.h"
#include "transition/generator/TransitionGenerator.h"
#include "temporary/generator/TemporaryGenerator.h"
#include "../common/Vector2.h"
#include "BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()
//#define GAME_NAME "__UNTITLED__"

class Controller;
class MouseStalker;

namespace SceneArgsStruct
{
	struct BaseArgs;
}

class SceneMng
{
public:
	static SceneMng& GetInstance(void)
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	void Run(void);

	const Vector2& GetWindowSize(void);				//�E�B���h�E�T�C�Y�擾
	std::shared_ptr<Controller> GetController(void);			//�R���g���[���[�擾

	void SetNextScene(SceneID nextSceneID, TransitionID nextTransitionID,
		std::shared_ptr<SceneArgsStruct::BaseArgs> nextSceneArgsPtr,
		std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> nextTransArgsPtr);
	void SetNextScene(TemporaryID nextTempID, std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> nextTempArgsPtr);

	void SetDeltaTimeFlg(bool flg);

private:
	SceneMng();
	~SceneMng();

	bool Init(void);
	bool SysInit(void);

	void Update(double delta);
	void Draw(void);

	void WindowTextRefresh(void);									//�E�B���h�E�̃e�L�X�g�̍X�V

	uniBaseScene ToNextScene(uniBaseScene ownScene);				//�V�[���ڍs�p�֐�
	uniBaseScene ToNextTempScene(uniBaseScene ownScene);			//�V�[���ڍs�p�֐�

	double time_;													//�o�ߎ���
	uniBaseScene scene_;											//���݂̃V�[��
	std::shared_ptr<Controller> controller_;						//�R���g���[���[

	SceneGenerator sceneGen_;										//�V�[�������p�N���X
	TransitionGenerator trGen_;										//�g�����W�V�����̐����p�N���X
	TemporaryGenerator tpGen_;

	SceneID nextSceneID_;																//���̃V�[����ID
	TransitionID nextTransitionID_;														//���̃g�����W�V������ID
	TemporaryID nextTemporaryID_;
	std::shared_ptr<SceneArgsStruct::BaseArgs> nextSceneArgs_;							//���̃V�[���̈����|�C���^
	std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> nextTransArgs_;		//���̃g�����W�V�����̈����|�C���^
	std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> nextTempArgs_;

	std::unique_ptr<MouseStalker> mouseStalker_;            //�}�E�X�X�g�[�J�[

	bool deltaTimeFlg;
};

