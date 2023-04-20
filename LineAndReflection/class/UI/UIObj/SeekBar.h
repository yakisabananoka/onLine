#pragma once
#include <functional>
#include <vector>
#include "BaseUI.h"

using SeekBarCallback = std::function<void(double)>;

class SeekBar :
    public BaseUI
{
public:
	SeekBar(Vector2Dbl firstPos, Vector2Dbl endPos);
    ~SeekBar();

	void Init(void)override;
	void Update(double delta)override;
	void SpotUpdate(std::shared_ptr<Controller> controller)override;		//���C���������Ă���ꍇ�Ɏ��s���鏈��
	void Draw(void)override;

	bool IsIntoMousePos(const Vector2Dbl& mousePos)override;				//�}�E�X�̍��W�Ƃ̓����蔻��`�F�b�N

	void SetUpdateCallback(SeekBarCallback func);

	const double& GetValue(void)const;
	void SetValue(double value);

	UIType GetUIType(void)override
	{
		return UIType::SeekBar;
	}
private:
	void ChangeValue(const Vector2Dbl& pos);

	std::shared_ptr<Controller> controller_;

	std::vector<SeekBarCallback> callbacks_;

	Vector2Dbl firstPos_;
	Vector2Dbl endPos_;

	double value_;

	bool flg_;
};

