#pragma once
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include <DxLib.h>
#include "../obj/usingObj.h"
#include "../common/shape/Capsule.h"
#include "../common/Vector2.h"

class Camera;

//�����\������m�[�h
struct Node
{
	enum class State
	{
		INCOMPLETE,		//������
		COMPLETE,		//����
		DISPOSAL		//�p��
	};
	Node(Vector2Dbl& p, State s, double dis) :pos(p), state(s), dist(dis) {}
	Vector2Dbl pos;
	State state;
	double dist;
};

struct ColInfo
{
	ColInfo(const int& id,const Capsule& cap):objId(id),capsule(cap){}
	int objId;
	Capsule capsule;
};

using ColorMap = std::unordered_map<Node::State, unsigned int>;
using NodeList = std::list<Node>;
using ColInfoPtr = std::unique_ptr<ColInfo>;

class BaseLine
{
public:
	enum class State
	{
		DRAWING,		//�`�撆
		STANDBY,		//�ҋ@��
		TOUCHING,		//�ڐG��
		DIE				//�폜�Ώ�
	};

	BaseLine(std::weak_ptr<Camera> camera, unsigned int color);
	~BaseLine();

	virtual void Update(double delta) = 0;
	virtual void UpdateAfterObj(double delta, ObjList& objList) {};			//�I�u�W�F�N�g�̃A�b�v�f�[�g��ɍs���֐�

	void Draw(void);

	virtual void SetPoint(Vector2Dbl pos) = 0;			//�_�̐ݒu
	void ClearPoint(void);								//�_�̈ꊇ����

	bool IsActive(void);								//�����t���O
	void SetActive(bool flg);							//�t���O�̐ݒ�

	virtual void EndDrawingLine(void) = 0;				//�I�[���ɌĂ�

	const NodeList& GetNodeList(void)const				//�m�[�h�̃��X�g���擾
	{
		return nodeList_;
	}
	const double& GetColRadius(void)const;				//�����蔻��̔��a���擾
	
	bool IsOverLength(void)const;						//�������I�[�o�[���Ă�����true��Ԃ�

	static void PreLoadLineScreen(void);				//���̃X�N���[���������炩���߃��[�h����

	void SetColObjInfo(ColInfoPtr ptr);					//�ڐG����Obj��ID�̓o�^

	size_t CountCompNode(void)const;					//�m��ς݃m�[�h�̌����J�E���g

	const State& GetState(void)const
	{
		return state_;
	}

	virtual bool HasCollision(void);					//�����蔻��������Ă��邩

	double GetTotalLength(void)const;					//�m��ς݃m�[�h�̑������v�Z

	double GetMaxLength(void)const;						//�ő勗���擾
protected:
	double GetMaxActiveTime(void);						//�ő吶���\���Ԃ̎擾
	void SetPolygon(float maxU);						//�`��p�|���S���̐ݒ�
	void SetPolygonAll(void);							//�S�Ă̕`��p�|���S���̐ݒ�
	
	void UpdateLineScreen(double delta);				//���n�̃A�b�v�f�[�g

	bool CheckSetPoint(const Vector2Dbl& setPos)const;	//�m�[�h�̒ǉ�����

	std::vector<VERTEX2D> vertexVec_;					//�`��p�|���S���̒��_�z��
	std::vector<VERTEX2D> bufferVertexVec_;				//�J�����I�t�Z�b�g���Z�p�̃o�b�t�@�Ƃ��Ă��炩���ߎ���Ă���
	std::vector<unsigned short> index_;					//�`��p�|���S���̒��_�̏���
	
	std::weak_ptr<Camera> camera_;						//�J����
	NodeList nodeList_;									//�m�[�h�̃��X�g

	std::vector<ColInfoPtr> colObjInfoVec_;				//Obj�Ƃ̏Փˏ��
	
	double time_;										//�C���X�^���X������̌o�ߎ���
	double activeTime_;									//���̊��S�L��������̌o�ߎ���
	State state_;										//���݂̏��
	Vector2Dbl milkyPos_;

	Vector2Dbl starWayHighPos_;
	Vector2Dbl starWayLowPos_;

	int lineR_;
	int lineG_;
	int lineB_;

private:
	void DrawLinePolygon(const Vector2Dbl& camOffset);	//�|���S���P�ʂŕ`��
	void DrawLineScreen(void);							//��

	double starWayCnt_;
	double starWayTime_;

};

