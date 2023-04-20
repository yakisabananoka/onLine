#pragma once
#include <memory>
#include <vector>
#include "usingObj.h"
#include "../collision/usingCollision.h"
#include "../common/Vector2.h"

class Camera;
class LineCtrl;
class Stage;
class UICtrl;
enum class ObjType;

class Obj
{
public:
	Obj(std::weak_ptr<Camera> camera, const Vector2Dbl& pos, const int& id);
	virtual ~Obj();

	virtual void Init(void) = 0;																			//������
	virtual void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage) = 0;		//�X�V
	virtual void ConfirmUpdate(double delta, const Stage& stage) {};										//�X�V�̊m��
	virtual void Draw(void) = 0;																			//�`��

	virtual void SetUI(UICtrl& uiCtrl) {};				//Obj�ʂ�UI�̐ݒ�

	virtual ObjType GetObjType(void)const = 0;			//ObjType�̎擾

	virtual bool IsUnit(void)const						//Unit���ǂ���
	{
		return false;
	}

	const Vector2Dbl& GetPos(void)const					//�ʒu�̎擾
	{
		return pos_;
	}

	const bool& GetSceneEndFlg(void)const				//�V�[�����I��������
	{
		return sceneEndFlg_;
	}

	const int& GetObjID(void)const						//�ŗLID�̎擾
	{
		return id_;
	}

	const ColPtr& GetColPtr(void)const					//�R���W�����̎擾
	{
		return colPtr_;
	}

	const bool& IsActive(void)const						//�L����Ԃ�
	{
		return activeFlg_;
	}

protected:
	Vector2Dbl GetCamOffset(void);			//�J�����I�t�Z�b�g�̎擾

	std::weak_ptr<Camera> camera_;			//�J����
	const Vector2Dbl defPos_;				//�����ʒu
	Vector2Dbl pos_;						//�ʒu
	bool sceneEndFlg_;						//�V�[���̏I���t���O
	const int id_;							//�ŗLID

	ColPtr colPtr_;							//�R���W����

	bool activeFlg_;						//�L���t���O

};

