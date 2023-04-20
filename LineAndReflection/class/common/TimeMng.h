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

	void Init(void);							//������

	double Update(void);						//�X�V

	double GetDeltaTime();						//�f���^�^�C���擾�p�֐�

	void SetTimeRate(double rate);				//���Ԃ̑��x�ݒ�

private:
	TimeMng();
	~TimeMng();

	std::chrono::system_clock::time_point now;		//���ݎ���
	std::chrono::system_clock::time_point old;		//�O�̃t���[���̎���

	double delta_;		//�f���^
	double rate_;		//���[�g
};

