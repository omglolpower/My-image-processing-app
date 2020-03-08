#pragma once
#include "vendor/stb_image/stb_image.h"
#include <string>
#include <vector>
struct sTextures
{
	std::string name="";
	int m_img_w = 0;
	int m_img_h = 0;
	int m_img_bpp = 0;
	std::string m_str_file;
	unsigned char* m_img;
	unsigned int m_texture = 0;
	sTextures();

	sTextures(std::string f);
};
struct sDefault_tex
{
	std::vector<sTextures> m_v_digits;
	std::vector<sTextures> m_v_lettersU;
	std::vector<sTextures> m_v_lettersL;
	std::vector<sTextures> m_v_other;
};