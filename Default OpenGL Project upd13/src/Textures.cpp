#include "Textures.h"

sTextures::sTextures()
{
}

sTextures::sTextures(std::string f)
{
	std::string ff = std::string("C:\\Application\\Textures") + f;
	m_img = stbi_load(ff.c_str(), &m_img_w, &m_img_h, &m_img_bpp, 4);
	
}
