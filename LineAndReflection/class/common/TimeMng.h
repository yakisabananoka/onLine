#pragma once
#include <chrono>

#define lpTimeMng TimeMng::GetInstance()

class TimeMng
{
public:
	static TimeMng& GetInstance(void)
	{
		static TimeMng s_Instance;
		return s_Instance;
	}

	void Init(void);							//初期化

	double Update(void);						//更新

	double GetDeltaTime();						//デルタタイム取得用関数

	void SetTimeRate(double rate);				//時間の速度設定

private:
	TimeMng();
	~TimeMng();

	std::chrono::system_clock::time_point now;		//現在時刻
	std::chrono::system_clock::time_point old;		//前のフレームの時刻

	double delta_;		//デルタ
	double rate_;		//レート
};

