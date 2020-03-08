#include "GUI.h"
static float sym_size = 0.05f;

cRect::cRect()
{
}

void cRect::center()
{
	for (char i = 0; i < 4; ++i)
	{
		x[i] += c[0]; y[i] += c[1];
	}
}

cRect::cRect(bool e, float c_x, float c_y, float a_in, float b_in, std::string n, sTextures t)

{
	exists = e;
	name = n;
	a = a_in;
	b = b_in;
	x[0] = a;
	x[1] = -a;
	x[2] = -a;
	x[3] = a;

	y[0] = b;
	y[1] = b;
	y[2] = -b;
	y[3] = -b;

	c[0] = c_x; c[1] = c_y;
	tex = t;
	center();
};

cText::cText() { t = ""; f[0] = 0.0f; f[1] = 0.0f; }

cText::cText(std::string tt, float ff[2],

	sDefault_tex def_tex

)
{
	t = tt;
	f[0] = ff[0];
	f[1] = ff[1];
	float start = f[0];
	for (char i = 0; i < tt.size(); ++i)
	{
		if (tt.at(i) == 46 )
		{
			std::string cs; cs.push_back(tt.at(i));
			cRect r(1, f[0], f[1], sym_size, sym_size, cs, def_tex.m_v_other.at(2));
			vR.push_back(r);
		}
		else if (tt.at(i) > 47 && tt.at(i) < 58)
		{
			std::string cs; cs.push_back(tt.at(i));
			cRect r(1, f[0], f[1], sym_size, sym_size, cs, def_tex.m_v_digits.at(tt.at(i) - 48));
			vR.push_back(r);
		}
		else if (tt.at(i) > 64 && tt.at(i) < 91)
		{
			std::string cs; cs.push_back(tt.at(i));
			cRect r(1, f[0], f[1], sym_size, sym_size, cs, def_tex.m_v_lettersU.at(tt.at(i) - 65));
			vR.push_back(r);
		}
		else if (tt.at(i) > 96 && tt.at(i) < 123)
		{
			std::string cs; cs.push_back(tt.at(i));
			cRect r(1, f[0], f[1]- sym_size*0.2f, sym_size*0.95f, sym_size*0.90f, cs, def_tex.m_v_lettersL.at(tt.at(i) - 97));
			vR.push_back(r);
		}
		else
		{
			std::string cs; cs.push_back('#');
			cRect r(1, f[0], f[1], sym_size, sym_size, cs, def_tex.m_v_other.at(0));
			vR.push_back(r);
		}
		f[0] += sym_size * 1.7f;
	}
}

cImg::cImg() {}

cImg::~cImg()
{
}

cImg::cImg( std::string str_text_in, sTextures texture_in, char number_in, sDefault_tex* def_tex_in)
{
	std::string m_str_text;
	m_number = number_in;
	m_img_rect = cRect::cRect(1, 0.3f, 0.9f-0.12f*static_cast<float>(m_number), 0.7f, 0.05f, str_text_in, texture_in);
	m_img_check_box = cRect::cRect(1, 0.8f, m_img_rect.c[1], 0.05f, 0.05f, "", (*def_tex_in).m_v_other.at(1));
}
