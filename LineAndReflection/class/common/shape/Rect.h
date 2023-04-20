#pragma once
#include "../Vector2.h"

struct Rect
{
	
	Rect();
	Rect(Vector2Dbl centerPos, double w, double h);
	Rect(Vector2Dbl LUPos, Vector2Dbl RDPos);

	Vector2Dbl pos;
	Vector2Dbl size;

	///辺の値の取得
	double Left(void)const;					//左辺
	double Right(void)const;				//右辺
	double Top(void)const;					//上辺
	double Bottom(void)const;				//下辺

	///辺の値の設定
	void SetLeft(double value);				//左辺
	void SetRight(double value);			//右辺
	void SetTop(double value);				//上辺
	void SetBottom(double value);			//下辺

	///サイズは固定したまま位置をずらす
	void SetFixedLeft(double value);		//左辺
	void SetFixedRight(double value);		//右辺
	void SetFixedTop(double value);			//上辺
	void SetFixedBottom(double value);		//下辺
	void SetFixedCC(Vector2Dbl cc);			//中心

	///各位置取得
	Vector2Dbl GetLT(void)const;			//左上
	Vector2Dbl GetLC(void)const;			//左中
	Vector2Dbl GetLB(void)const;			//左下
	Vector2Dbl GetCT(void)const;			//中央上
	Vector2Dbl GetCC(void)const;			//中心
	Vector2Dbl GetCB(void)const;			//中央下
	Vector2Dbl GetRT(void)const;			//右上
	Vector2Dbl GetRC(void)const;			//右中
	Vector2Dbl GetRB(void)const;			//右下

	///リセット
	void Reset(Vector2Dbl centerPos, double w, double h);
	void Reset(Vector2Dbl LUPos, Vector2Dbl RDPos);

	bool InShape(Vector2Dbl checkPos)const;

	bool CheckHit(const Rect& rect)const;
};

