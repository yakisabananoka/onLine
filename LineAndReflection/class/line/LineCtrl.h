#pragma once
#include <memory>
#include <functional>
#include <array>
#include <list>
#include <string>
#include <utility>
#include "../input/Controller.h"
#include "usingLine.h"
#include "../obj/usingObj.h"

class LineGenerator;
class Camera;
class UICtrl;
class Gauge;
class Stage;
struct Capsule;
struct Node;

class LineCtrl
{
public:
	LineCtrl(std::weak_ptr<Camera> camera, std::string genLineName);
	~LineCtrl();

	void Init(void);
	void InitUI(UICtrl& uiCtrl);

	void Update(double delta, const Stage& stage);									//�X�V
	void UpdateAfterObj(double delta, ObjList& objList);							//Obj�̃A�b�v�f�[�g��Ɏ��s
	void Draw(void);																//�`��

	void GetLineInfoCap(std::function<bool(const Capsule&, LinePtr&)> func);		//���̏����J�v�Z���P�ʂœn��
	void GetLineInfoNode(std::function<bool(const Node&, LinePtr&)> func);			//���̏����m�[�h�P�ʂœn��

	void CancelLastLine(void);							//���O�̐���������

	const double& GetTotalLineDist(void)const			//���̋����̍��v�̎擾
	{
		return totalLineDist_;
	}

private:

	std::shared_ptr<Controller> controller_;		//�R���g���[���[
	std::weak_ptr<Camera> camera_;					//�J����
	std::list<LinePtr> lineList_;					//���̔z��
	std::array<std::string, 3> lineTypeList_;		//���C���̎�ނ̔z��

	std::unique_ptr<LineGenerator> generator_;		//���C���̃W�F�l���[�^�[

	std::string genLineName_;						//����������̖��O

	int genLineNum_;								//����������̔ԍ�

	double totalLineDist_;							//���̋����̍��v
	double switchTime_;								//�؂�ւ�����
};
