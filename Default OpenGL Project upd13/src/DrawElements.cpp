#include "DrawElements.h"
static unsigned int indicesQuad[] = {
	0,1,3,
	1,2,3
};
//DRAW
static float sym_size = 0.05f;

float positionsQuad[4 * 8] = {
0.5f,
0.5f,
0.0f,

1.0f,
0.0f,
0.0f,

0.0f,
1.0f,

-0.5f,
0.5f,
0.0f,

0.0f,
1.0f,
0.0f,

0.0f,
0.0f,

-0.5f,
-0.5f,
0.0f,

0.0f,
0.0f,
1.0f,

1.0f,
0.0f,

 0.5f,
-0.5f,
0.0f,

0.0f,
0.0f,
1.0f,

1.0f,
1.0f
};

//stbi_set_flip_vertically_on_load(0);
//unsigned char** img;


void Draw(unsigned int& prog, unsigned int& VAO , cRect r
	//, unsigned int & tex
	)
{

	
	for (char i = 0; i < 4; ++i)
	{
		positionsQuad[0 + 8 * i] = r.x[i];
		positionsQuad[1 + 8 * i] = r.y[i];

	}
	//glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
	////texcoord
	//unsigned int attLocTex = glGetAttribLocation(prog, "vertex_texcoord");
	//glVertexAttribPointer(attLocTex, 2, GL_FLOAT, false, sizeof(float) * 8, (GLvoid*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(attLocTex);
	//pos[0] += 0.01f;
	//color
	// position
	
	
	
	/*glBindTexture(GL_TEXTURE_2D, tex);




	if (img)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_w, img_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else { LOG("ERROR::TEXTURE LOADING FAILED"); }*/
	       glGenTextures(1, &r.tex.m_texture);
		   
			   glBindTexture(GL_TEXTURE_2D, r.tex.m_texture);
			   if (r.tex.m_img)
			   {
				   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, r.tex.m_img_w, r.tex.m_img_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, r.tex.m_img);
				   glGenerateMipmap(GL_TEXTURE_2D);
			   }
			   else { LOG("ERROR::TEXTURE LOADING FAILED"); }
			
		   
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionsQuad), positionsQuad, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesQuad), indicesQuad, GL_STATIC_DRAW);
	unsigned int attLocPos = glGetAttribLocation(prog, "vertex_position");
	glVertexAttribPointer(attLocPos, 3, GL_FLOAT, false, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(attLocPos);
	unsigned int attLocCol = glGetAttribLocation(prog, "vertex_color");
	glVertexAttribPointer(attLocCol, 3, GL_FLOAT, false, sizeof(float) * 8, (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(attLocCol);
	unsigned int attLocTex = glGetAttribLocation(prog, "vertex_texcoord");
	glVertexAttribPointer(attLocTex, 2, GL_FLOAT, false, sizeof(float) * 8, (GLvoid*)(6 * sizeof(float)));
	glEnableVertexAttribArray(attLocTex);
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//positionsQuad[0] += 0.01f;
	//glDeleteBuffers(1, &VAO);
	glDeleteTextures(1, &r.tex.m_texture);
	

}

void Draw1(unsigned int& prog, unsigned int& VAO, cRect r, std::string s_text, sDefault_tex* def_tex
	//, unsigned int & tex
)
{
	Draw(prog, VAO, r
		//, unsigned int & tex
	);
	if(s_text!="")
	for (char i = 0; i < s_text.size(); ++i)
	{
		float pos[2] = { r.c[0]-r.a+ sym_size, r.c[1] };
		cText t(s_text, pos, *def_tex);
		Draw(prog, VAO, t.vR.at(i)
			//, unsigned int & tex
		);
	}
}


void DrawImg(unsigned int& prog, unsigned int& VAO, sDefault_tex *def_tex, std::vector<cImg>& v_images_in)
{
	for (char i = 0; i < v_images_in.size(); ++i)
	{
		Draw1(prog, VAO, v_images_in.at(i).m_img_rect, v_images_in.at(i).m_img_rect.name, def_tex);
		if (v_images_in.at(i).checked)
		{
			LOG("DRAW CHECK BOX");
			Draw(prog, VAO, v_images_in.at(i).m_img_check_box);
		}
	}
}