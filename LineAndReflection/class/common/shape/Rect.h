#pragma once
#include "../Vector2.h"

struct Rect
{
	
	Rect();
	Rect(Vector2Dbl centerPos, double w, double h);
	Rect(Vector2Dbl LUPos, Vector2Dbl RDPos);

	Vector2Dbl pos;
	Vector2Dbl size;

	///�ӂ̒l�̎擾
	double Left(void)const;					//����
	double Right(void)const;				//�E��
	double Top(void)const;					//���
	double Bottom(void)const;				//����

	///�ӂ̒l�̐ݒ�
	void SetLeft(double value);				//����
	void SetRight(double value);			//�E��
	void SetTop(double value);				//���
	void SetBottom(double value);			//����

	///�T�C�Y�͌Œ肵���܂܈ʒu�����炷
	void SetFixedLeft(double value);		//����
	void SetFixedRight(double value);		//�E��
	void SetFixedTop(double value);			//���
	void SetFixedBottom(double value);		//����
	void SetFixedCC(Vector2Dbl cc);			//���S

	///�e�ʒu�擾
	Vector2Dbl GetLT(void)const;			//����
	Vector2Dbl GetLC(void)const;			//����
	Vector2Dbl GetLB(void)const;			//����
	Vector2Dbl GetCT(void)const;			//������
	Vector2Dbl GetCC(void)const;			//���S
	Vector2Dbl GetCB(void)const;			//������
	Vector2Dbl GetRT(void)const;			//�E��
	Vector2Dbl GetRC(void)const;			//�E��
	Vector2Dbl GetRB(void)const;			//�E��

	///���Z�b�g
	void Reset(Vector2Dbl centerPos, double w, double h);
	void Reset(Vector2Dbl LUPos, Vector2Dbl RDPos);

	bool InShape(Vector2Dbl checkPos)const;

	bool CheckHit(const Rect& rect)const;
};

