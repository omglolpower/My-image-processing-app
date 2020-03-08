#pragma once
#include <string>
#include <vector>
#include "Textures.h"
class cRect
{
public:

	cRect();
	bool exists;
	std::string name;
	char pos=0;
	float a = 1.0f;
	float b = 1.0f;
	float x[4] = { a, -a, -a, a };
	float y[4] = { b, b, -b, -b };
	float c[2] = { 0.0f, 0.0f };
	sTextures tex;
	bool pressed = false;
	void center();
	cRect(bool e, float c_x, float c_y, float a_in, float b_in, std::string n, sTextures t);
};

class cText
{
public:
	std::vector<cRect> vR;
	std::string t;
	float f[2] = { 0.0f , 0.0f };
	cText();
	cText(std::string tt, float ff[2],


		sDefault_tex def_tex
	);
};

class cImg
{
public:
	cImg();
	~cImg();
	char m_number = 0;
	cImg( std::string str_text_in, sTextures texture_in, char number_in, sDefault_tex* def_tex_in);
	cRect m_img_rect;
	cRect m_img_check_box;
	bool checked = false;


};
