#include <chrono>
#include "TimeMng.h"

constexpr int NANO = 1000000000;

void TimeMng::Init(void)
{
	now = std::chrono::system_clock::now();
	delta_ = 0.0f;
}

double TimeMng::Update(void)
{
	old = now;
	now = std::chrono::system_clock::now();
	delta_= static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(now - old).count()) / NANO;

	if (delta_ > 0.5)
	{
		delta_ = 0.0;
	}

	return delta_ * rate_;
}

double TimeMng::GetDeltaTime()
{
	return delta_ * rate_;
}

void TimeMng::SetTimeRate(double rate)
{
	rate_ = rate;
}

TimeMng::TimeMng()
{
	delta_ = 0.0;
	rate_ = 1.0;
}

TimeMng::~TimeMng()
{
}
