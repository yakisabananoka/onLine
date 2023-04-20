#pragma once
#include <memory>
#include <vector>
#include <string>
#include "BaseUI.h"
#include "../UIObj/usingImagePanel.h"

class SlideList :
    public BaseUI
{
public:
	enum class Dir
	{
		Up,
		Down,
		Left,
		Right
	};

	SlideList(Rect range,std::string key);
    ~SlideList();

	void Init(void)override;
	void InitUI(void);
	void Update(double delta)override;
	void SpotUpdate(std::shared_ptr<Controller> controller)override;		//���C���������Ă���ꍇ�Ɏ��s���鏈��
	void Draw(void)override;

	bool IsIntoMousePos(const Vector2Dbl& mousePos)override;				//�}�E�X�̍��W�Ƃ̓����蔻��`�F�b�N

	UIType GetUIType(void)override
	{
		return UIType::SlideList;
	}

private:
	std::unique_ptr<std::string> frameImage_;
	std::string scrKey_;
	std::string image_;


};

