#pragma once

struct Color
{
	int r;
	int g;
	int b;

	Color();
	Color(int r, int g, int b);
	Color(unsigned int color);
	~Color() {};

	unsigned int GetColorCode(void)const;		//DX���C�u�����`���ł̐F�擾
};

