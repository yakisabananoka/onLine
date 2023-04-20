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

	unsigned int GetColorCode(void)const;		//DXライブラリ形式での色取得
};

