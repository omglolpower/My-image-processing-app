#pragma once
#include "opengl.h"
#include "vendor/stb_image/stb_image.h"
#include <iostream>
#include "GUI.h"
#include "Textures.h"
#define LOG(x) std::cout<<x<<std::endl

void Draw(unsigned int& prog, unsigned int& VAO, cRect r
	//, unsigned int & tex
);
void Draw1(unsigned int& prog, unsigned int& VAO, cRect r, std::string s_text, sDefault_tex* def_tex
	//, unsigned int & tex
	);
void DrawImg(unsigned int& prog, unsigned int& VAO, sDefault_tex* def_tex, std::vector<cImg>& v_images_in);