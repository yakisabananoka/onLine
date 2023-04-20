#pragma once
class Easing
{
public:
	Easing() {};
	~Easing() {};

	//Inån
	double InQuad(double time, double startVal, double deltaVal, double total)const;
	double InCubic(double time, double startVal, double deltaVal, double total)const;
	double InQuart(double time, double startVal, double deltaVal, double total)const;
	double InQuint(double time, double startVal, double deltaVal, double total)const;
	double InExpo(double time, double startVal, double deltaVal, double total)const;
	double InCirc(double time, double startVal, double deltaVal, double total)const;
	double InBack(double time, double startVal, double deltaVal, double total)const;

	//Outån
	double OutQuad(double time, double startVal, double deltaVal, double total)const;
	double OutCubic(double time, double startVal, double deltaVal, double total)const;
	double OutQuart(double time, double startVal, double deltaVal, double total)const;
	double OutQuint(double time, double startVal, double deltaVal, double total)const;
	double OutExpo(double time, double startVal, double deltaVal, double total)const;
	double OutCirc(double time, double startVal, double deltaVal, double total)const;
	double OutBack(double time, double startVal, double deltaVal, double total)const;

	//InOutån
	double InOutQuad(double time, double startVal, double deltaVal, double total)const;
	double InOutCubic(double time, double startVal, double deltaVal, double total)const;
	double InOutQuart(double time, double startVal, double deltaVal, double total)const;
	double InOutQuint(double time, double startVal, double deltaVal, double total)const;
	double InOutExpo(double time, double startVal, double deltaVal, double total)const;
	double InOutCirc(double time, double startVal, double deltaVal, double total)const;
	double InOutBack(double time, double startVal, double deltaVal, double total)const;

};

