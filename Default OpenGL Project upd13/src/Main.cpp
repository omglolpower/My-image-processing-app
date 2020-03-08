
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include "ListFiles.h"
//#include "vendor/SOIL/SOIL.h"
#include "vendor/stb_image/stb_image.h"
#include "opengl.h"
#include <iterator>
#include "DrawElements.h"
#include "ReadDirectory.h"
#include "InitWindow.h"
#include "Controls.h"
#include "opencv/opencv.h"
#include "opencv/convert.h"
#include "opencv/Histogram.h"
#include "opencv/Levels.h"
#include "opencv/blocks.h"
#include "opencv/DCT.h"
#include "opencv/Gauss.h"
#include "opencv/Canny.h"
#include "opencv/morph.h"
#include "opencv/pseudoColor.h"
const int w_width = 500;
const int w_height = 500;

static int blockSize = 32;

int frameBufferWidth = 0;
int frameBufferHeight = 0;
GLFWwindow* window;
unsigned int enterCounter = 0;

std::vector<short>* input = new std::vector<short>;

#define LOG(x) std::cout<<x<<std::endl

//struct vVertex
//{
//	float position[3]; float color[3]; float texcoord[2];
//};
bool loadShaders(GLuint& program)
{
	bool loadSuccess = true;
	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	//Vertex
	in_file.open("C:\\Application\\Shaders\\core_vertex_shader.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
		{
			src += temp + '\n';
		}
		in_file.close();

	}
	else 
	{
		loadSuccess = false;
		LOG("shader load failed::open vertex file failed");
	}
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		LOG("shader load failed::compile vertex shader failed");
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		LOG(infoLog);
		loadSuccess = false;

	}

	temp = ""; src = "";

	//Fragment
	in_file.open("C:\\Application\\Shaders\\core_fragment_shader.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
		{
			src += temp + '\n';
		}
		in_file.close();
	}
	else
	{
		loadSuccess = false;
		LOG("shader load failed::open fragment file failed");
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		LOG("shader load failed::compile fragment shader  failed");
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		LOG(infoLog);
		loadSuccess = false;
	}

	temp = ""; src = "";

	//program

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		LOG("program link error");
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		LOG(infoLog);
	}

	//end
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSuccess;
}

void updateInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

struct Vertex
{
	float position[3];
	float color[3];
	float texcoord[2];
};
unsigned int vert_count = 3;

float positions[3 * 8] = {
0.5f,
-0.5f,
0.0f,

1.0f,
0.0f,
0.0f,

0.0f,
1.0f,

0.0f,
0.5f,
0.0f,

0.0f,
1.0f,
0.0f,

0.0f,
0.0f,

-0.5f,
- 0.5f,
0.0f,

0.0f,
0.0f,
1.0f,

1.0f,
0.0f
};

unsigned int indices[] = { 0,1,3 };
unsigned int indicesQuad[] = {
	0,1,3,
	1,2,3
};




void buff()
{
	

}

double cursor_x = 0.0, cursor_y = 0.0;
int ww = 0, hh = 0;
int LMB = 0;

bool press(cRect &r)
{
	return pressObj(window, cursor_x, cursor_y, ww, hh, r, LMB);
}
bool pressNot(cRect& r)
{
	return pressNotObj(window, cursor_x, cursor_y, ww, hh, r, LMB);
}

sDefault_tex* def_tex = new sDefault_tex;

std::vector<std::string>* v_img_name = new std::vector<std::string>;

std::vector<cImg> v_images;

void Read(std::vector<std::string>& dd, std::string c )
{
	dd.clear();

	v_stringvec v;
	std::vector<std::string> d;
	read_directory(c, v);
	std::copy(v.begin(), v.end(),
		std::ostream_iterator<std::string>(std::cout, "\n"));
	d.resize(v.size());
	for (char i = 0; i < v.size(); ++i)
	{
		for (char j = v.at(i).size() - 1; v.at(i).at(j) != 92; --j)
		{
			d.at(i).push_back(v.at(i).at(j));
		}
	}
	dd.resize(d.size());
	for (char i = 0; i < d.size(); ++i)
	{
		for (char j = d.at(i).size() - 1; j >= 0; --j)
		{
			dd.at(i).push_back(d.at(i).at(j));
		}
	}
	for (char i = 0; i < dd.size(); ++i)
		LOG(dd.at(i));
}

unsigned int core_program;
unsigned int VAO;
std::vector<cRect>* v_options = new std::vector<cRect>;
std::vector<cRect>* v_sub_options = new std::vector<cRect>;
std::vector<cRect>* v_filters = new std::vector<cRect>;


void DrawAllImg()
{
	DrawImg(core_program, VAO, def_tex, v_images);
}
void DrawObj(cRect& r)
{
	Draw1(core_program, VAO, r, r.name, def_tex);
}
std::vector<cv::Mat> v_cv_images;

void showChosen()
{
	for (char i = 0; i < v_cv_images.size(); ++i)
	{
		if (v_images.at(i).checked)
		{
			std::string str_window = "img ";
			str_window.push_back(i+48);
			cv::imshow(str_window, v_cv_images.at(i));
		}
	}
	cv::waitKey();
}
std::vector<cv::Mat>* v_proc_images = new std::vector<cv::Mat>;

void showProc()
{
	for (char i = 0; i < v_proc_images->size(); ++i)
	{
		std::string str_window = "img ";
		str_window.push_back(i + 48);
		cv::imshow(str_window, v_proc_images->at(i));
	}
	cv::waitKey();
}


void convertAllToY()
{
	for (char i = 0; i < v_cv_images.size(); ++i)
	{
		if (v_images.at(i).checked)
		v_proc_images->push_back(convert_to_Y(v_cv_images.at(i)));
	}
}
void histAll()
{
	for (char i = 0; i < v_cv_images.size(); ++i)
	{
		if (v_images.at(i).checked)
			v_proc_images->push_back(getHist(v_cv_images.at(i)));
	}
}

void two_tones_all()
{
	for (char i = 0; i < v_cv_images.size(); ++i)
	{
		cv::Mat c = convert_to_Y(v_cv_images.at(i));
		if (v_images.at(i).checked)
			v_proc_images->push_back(two_tones(c));
	}
}

unsigned char levels = 40;
void levelsAll()
{
	for (char i = 0; i < v_cv_images.size(); ++i)
	{
		if (v_images.at(i).checked)
			v_proc_images->push_back(ChangeLevelsCount(v_cv_images.at(i), levels, 1.0f));
	}
}

int mouse_x = 0, mouse_y = 0;
unsigned int writeCounter = 20;
unsigned int eraseCounter = 20;

void write(cRect& r_in)
{
	bool pressed = false;

	char c = '\0';
	
		for (char i = 48; i < 58; ++i)
		{
			if (glfwGetKey(window, i) == GLFW_PRESS)
			{
				pressed = true;
				c = i;
				break;
			}
			else
			{
				pressed = false;
			}
		}

		if (pressed) ++writeCounter;
		else writeCounter = 20;
	if (writeCounter == 21)
	{
		r_in.name.push_back(c);
	}
	bool pressedBS = false;

		if (glfwGetKey(window, 259) == GLFW_PRESS)
		{
			pressedBS = true;
		}
		else
		{
			eraseCounter = 20;
			pressedBS = false;
		}
		
	if (pressedBS) ++eraseCounter;

	if (eraseCounter == 21 && r_in.name.size()>0)
	{
		r_in.name.pop_back();
	}
	if (r_in.name.size() > 0 && r_in.name.at(0) == 48)
	{
		r_in.name.erase(r_in.name.begin());
	}
}

void write1(cRect& r_in)
{
	if (!r_in.pressed && press(r_in))
	{
		r_in.pressed = true;
		++LMB;
	}
	if (r_in.pressed)
	{
		write(r_in);
		LOG(r_in.name);
	}
	if (r_in.pressed && pressNot(r_in))
	{
		++LMB;
		r_in.pressed = false;
	}
}

bool pressed = false;
static void onMouse(int event, int x, int y, int, void*)
{
	if (event != cv::EVENT_LBUTTONDOWN)
		return;
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
		mouse_x = x;
		mouse_y = y;
		pressed = true;
	}
}

void DCTAll()
{
	for (char i = 0; i < v_cv_images.size(); ++i)
	{
		if (v_images.at(i).checked)
		{
			cv::Mat imageWithBlocks = blocks(v_cv_images.at(i));
			cv::imshow("blocks", imageWithBlocks);

			cv::setMouseCallback("blocks", onMouse);
			int blockX, blockY;
			cv::waitKey();

			for (int row = 0; row < imageWithBlocks.rows; row = row + blockSize) {
				for (int col = 0; col < imageWithBlocks.cols; col = col +
					blockSize) {
					if ((mouse_y >= row) && (mouse_y < row + blockSize) && (mouse_x >= col) && (mouse_x
						< col + blockSize)) {
						blockY = row;
						blockX = col;
					}
				}
			}

			cv::Rect block = cv::Rect(blockX, blockY, blockSize, blockSize);
			cv::Mat imageBlock = imageWithBlocks(block);
			rectangle(imageWithBlocks, block, cv::Scalar(0, 0, 255));

			cv::imshow("12321", imageWithBlocks);
			//cv::waitKey();
			cv::Mat DCT_img = DCT(imageBlock);
			//cv::imshow("12321", imageBlock);
			//cv::imshow("12322", DCT_img);

			cv::waitKey();
			v_proc_images->push_back(DCT_img);

		}
	}
}

void GaussAll3()
{
	for (char i = 0; i < v_cv_images.size(); ++i)
	{
		if (v_images.at(i).checked)
			v_proc_images->push_back(gauss3(v_cv_images.at(i)));
	}
}

void GaussAll5()
{
	for (char i = 0; i < v_cv_images.size(); ++i)
	{
		if (v_images.at(i).checked)
			v_proc_images->push_back(gauss5(v_cv_images.at(i)));
	}
}

void cannyAll()
{
	for (char i = 0; i < v_cv_images.size(); ++i)
	{
		if (v_images.at(i).checked)
			v_proc_images->push_back(canny(v_cv_images.at(i)));
	}
}

void MGall()
{
	for (char i = 0; i < v_cv_images.size(); ++i)
	{
		if (v_images.at(i).checked)
			v_proc_images->push_back(MG(v_cv_images.at(i)));
	}
}
void YtoColorAll()
{
	for (char i = 0; i < v_cv_images.size(); ++i)
	{
		if (v_images.at(i).checked)
			v_proc_images->push_back(pseudoColor(v_cv_images.at(i)));
	}
}

void readImgFromDir()
{
	v_img_name->clear();
	v_images.clear();
	v_cv_images.clear();
	Read(*v_img_name, "C:\\Application\\Images");
	for (char i = 0; i < (*v_img_name).size(); ++i)
	{
		cImg createImg((*v_img_name).at(i), (*def_tex).m_v_other.at(0), i, def_tex);
		//createImg.checked = true;
		v_images.push_back(createImg);
	}
	for (char i = 0; i < v_images.size(); ++i)
	{
		v_cv_images.push_back(cv::imread(std::string("C:\\Application\\Images\\") + (*v_img_name).at(i)));
	}
}

int main()
{
	
	
	std::vector<std::string> dd;

	Read( dd, "C:\\Application\\Textures\\symbols\\digits");

	for (char i = 0; i < dd.size(); ++i)
	{
		sTextures tt(std::string("\\symbols\\digits\\") + dd.at(i));
		(*def_tex).m_v_digits.push_back(tt);
	}

	Read(dd, "C:\\Application\\Textures\\symbols\\letters\\Lower");

	for (char i = 0; i < dd.size(); ++i)
	{
		sTextures tt(std::string("\\symbols\\letters\\Lower\\") + dd.at(i));
		(*def_tex).m_v_lettersL.push_back(tt);
	}

	Read(dd, "C:\\Application\\Textures\\symbols\\letters\\Upper");

	for (char i = 0; i < dd.size(); ++i)
	{
		sTextures tt(std::string("\\symbols\\letters\\Upper\\") + dd.at(i));
		(*def_tex).m_v_lettersU.push_back(tt);
	}

	(*def_tex).m_v_other.push_back(sTextures::sTextures("\\tab.png"));

	(*def_tex).m_v_other.push_back(sTextures::sTextures("\\check.png"));

	(*def_tex).m_v_other.push_back(sTextures::sTextures("\\symbols\\other\\dot.png"));

	
	(*def_tex).m_v_other.push_back(sTextures::sTextures("\\tab1.png"));

	(*def_tex).m_v_other.push_back(sTextures::sTextures("\\upd.png"));


	readImgFromDir();


	//delete v_img_name;
	initWindow(window, w_width, w_height);

	
	glfwSetFramebufferSizeCallback(window, frame_buffer_resize_callback);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);

	std::string s1 = "sgargg35454gWeeW";
	float fff[2] = { 0.0f, 0.0f };
	cText t1(s1, fff, *def_tex);
	

	// opengl options

	/*glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
*/

	

	//init shader
	loadShaders(core_program);
	if (!loadShaders(core_program))
		glfwTerminate();



	//MODEL


	// VAO, VBO, EBO
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	//GEN VBO and  send data 

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//float* f_vertices = new float[vertices->position.size() + vertices->color.size() + vertices->texcoord.size()];
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4, positionsQuad, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//float* f_vertices = new float[vertices->position.size() + vertices->color.size() + vertices->texcoord.size()];

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	

	


	glBindVertexArray(0);

	// texture init

	
	
	
	double tab[4] = { -1.0f + 0.3f, 1.0f - 0.1f, 0.3f, 0.1f };
	std::vector<cRect>* v_objects = new std::vector<cRect>;
	std::string options = "Options";
	cText t_options();
	
	(*v_objects).push_back(cRect::cRect(false, 0.0f, 0.0f, 0.3f, 0.3f, "", (*def_tex).m_v_digits.at(0)));
	(*v_objects).push_back(cRect::cRect(true, tab[0], tab[1], tab[2], tab[3], "Options", (*def_tex).m_v_other.at(0)));
	(*v_objects).push_back(cRect::cRect(false, tab[0]+0.2f, 0.0f - tab[3], tab[2]+0.2f, 1.0f - tab[3], "", (*def_tex).m_v_other.at(0)));
	(*v_objects).push_back(cRect::cRect(false, 0.0f, 0.0f, 0.2f, 0.2f, "", (*def_tex).m_v_other.at(1)));

	(*v_objects).push_back(cRect::cRect(true, 0.9f, -0.9f, 0.05f, 0.05f, "", (*def_tex).m_v_other.at(4)));
	(*v_objects).push_back(cRect::cRect(false, 0.0f, 0.0f, 0.2f, 0.2f, "", (*def_tex).m_v_other.at(3)));

	v_sub_options->push_back(cRect::cRect(false, 0.0f, 0.2f, 1.0f, 0.2f, "Enter levels 0 to 255", (*def_tex).m_v_other.at(0)));
	v_sub_options->push_back(cRect::cRect(false, 0.0f, -0.2f, 0.2f, 0.2f, "", (*def_tex).m_v_other.at(3)));

	(*v_options).push_back(cRect::cRect(false, tab[0], tab[1] - 0.15f, tab[2], tab[3] * 0.6f, "Show", (*def_tex).m_v_other.at(3)));
	(*v_options).push_back(cRect::cRect(false, tab[0], tab[1] - 0.30f, tab[2], tab[3] * 0.6f, "Gray", (*def_tex).m_v_other.at(3)));
	(*v_options).push_back(cRect::cRect(false, tab[0], tab[1] - 0.45f, tab[2], tab[3] * 0.6f, "Hist", (*def_tex).m_v_other.at(3)));
	(*v_options).push_back(cRect::cRect(false, tab[0], tab[1] - 0.60f, tab[2], tab[3] * 0.6f, "Levels", (*def_tex).m_v_other.at(3)));
	(*v_options).push_back(cRect::cRect(false, tab[0], tab[1] - 0.75f, tab[2], tab[3] * 0.6f, "DCT", (*def_tex).m_v_other.at(3)));
	(*v_options).push_back(cRect::cRect(false, tab[0], tab[1] - 0.90f, tab[2], tab[3] * 0.6f, "Filters", (*def_tex).m_v_other.at(3)));
	(*v_options).push_back(cRect::cRect(false, tab[0], tab[1] - 1.05f, tab[2], tab[3] * 0.6f, "2tones", (*def_tex).m_v_other.at(3)));
	(*v_options).push_back(cRect::cRect(false, tab[0]+0.15f, tab[1] - 1.20f, tab[2]+0.15f, tab[3] * 0.6f, "Y.to.color", (*def_tex).m_v_other.at(3)));


	(*v_filters).push_back(cRect::cRect(false, -0.3f, 0.0f, 0.5f, 0.9f, "", (*def_tex).m_v_other.at(3)));

	(*v_filters).push_back(cRect::cRect(false, -0.3f, 0.0f + 0.75f, 0.48f, tab[3] * 0.6f, "Gauss 3x3", (*def_tex).m_v_other.at(0)));
	(*v_filters).push_back(cRect::cRect(false, -0.3f, 0.0f + 0.60f, 0.48f, tab[3] * 0.6f, "Gauss 5x5", (*def_tex).m_v_other.at(0)));
	(*v_filters).push_back(cRect::cRect(false, -0.3f, 0.0f + 0.45f, 0.48f, tab[3] * 0.6f, "Canny", (*def_tex).m_v_other.at(0)));
	(*v_filters).push_back(cRect::cRect(false, -0.3f, 0.0f + 0.30f, 0.48f, tab[3] * 0.6f, "Morph Grad", (*def_tex).m_v_other.at(0)));




	
	/*if (img2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_w2, img_h2, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else { LOG("ERROR::TEXTURE LOADING FAILED"); }*/
	//glActiveTexture(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glfwSwapInterval(1);
	//SOIL_free_image_data(img);
	bool b_write = false;


	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) ++LMB; else LMB = 0;
		if (glfwGetKey(window, 257) == GLFW_PRESS) ++enterCounter; else enterCounter = 0;

		// upd input
		glfwPollEvents();

		// upd ---
		updateInput(window);
		//draw---

		// clear
		glClearColor(45.0f/256.0f, 45.0f/ 256.0f, 48.0f/ 256.0f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
		// use program
		//glBindTexture(GL_TEXTURE_2D, texture0);

		glUseProgram(core_program);

		//glUniform1i(glGetUniformLocation(core_program, "texture0"), 0);

		// UPD UNIFORMS

		//ACRIVATE TEXTURE

		

		//DRAW
		
		//texcoord
		glfwGetCursorPos(window, &cursor_x, &cursor_y);
		glfwGetWindowSize(window, &ww, &hh);

		std::cout << "Cursor: x -- " << cursor_x << " ;  y -- " << cursor_y << ' '<< ww <<' '<< hh<< std::endl;
		for (char i = 0; i < (*v_objects).size(); ++i)
		{
			if ((*v_objects).at(i).exists)
			{
				Draw1(core_program, VAO, (*v_objects).at(i), (*v_objects).at(i).name, (def_tex));
			}
		}




		if (press(v_objects->at(4)))
		{
			readImgFromDir();
		}
		if (press((*v_objects).at(1)) && !(*v_objects).at(2).exists)
		{
			(*v_objects).at(2).exists = true;
			for (char i = 0; i < v_options->size(); ++i)
			{
				v_options->at(i).exists = true;
			}
			++LMB;
		}
		if(pressNot((*v_objects).at(2))&& (*v_objects).at(2).exists)
		{
			(*v_objects).at(2).exists = false;
			for (char i = 0; i < v_options->size(); ++i)
			{
				v_options->at(i).exists = false;
			}
			++LMB;
		}
		if ((*v_objects).at(2).exists)
		{
			for (char i = 0; i < v_options->size(); ++i)
			{
				DrawObj(v_options->at(i));
				if (press((*v_options).at(i)))
				{
				
					switch (i)
					{
					case 0:
						showChosen();
						break;
					case 1:
						convertAllToY();
						showProc();
						v_proc_images->clear();
						break;
					case 2:
						histAll();
						showProc();
						v_proc_images->clear();
						break;
					case 3:
						

						v_sub_options->at(0).exists = true;
						v_sub_options->at(1).exists = true;
						break;
					case 4:
						DCTAll();
						showProc();
						v_proc_images->clear();
						break;
					case 5:
						LOG("PRESSED FILTERS");
						v_filters->at(0).exists = true;
						break;
					case 6:
						two_tones_all();
						showProc();
						v_proc_images->clear();
						break;
					case 7:
						YtoColorAll();
						showProc();
						v_proc_images->clear();
						break;
					default:
						break;
					}
				}
				

			}
			
		}
		/*for (char i = 0; i < t1.vR.size(); ++i)
		{
			Draw(core_program, VAO, t1.vR.at(i));
		}*/
		//Draw(core_program, VAO, v_objects.at(3));
		//Draw1(core_program, VAO, img123.m_img_rect, img123.m_img_rect.name, def_tex);
		DrawAllImg();
		for (char i = 0; i < v_images.size(); ++i)
		{
			if (press(v_images.at(i).m_img_rect)&&!v_filters->at(0).exists)
			{
				if (!v_images.at(i).checked)
				{
					v_images.at(i).checked = true;
					++LMB;
				}
				else
				{
					v_images.at(i).checked = false;
					++LMB;
				}
			}
		}
		

		
		
		if (v_sub_options->at(1).exists)
		{
			DrawObj(v_sub_options->at(0));
			DrawObj(v_sub_options->at(1));
			write1(v_sub_options->at(1));
			if (enterCounter == 1)
			{
				if (v_sub_options->at(1).name.size() > 3)
				{
					LOG("ERROR:: too many digits");
					v_sub_options->at(1).name.clear();
				}
				else if (v_sub_options->at(1).name.size() == 0)
				{
					LOG("ERROR:: enter digits");
				}
				else
				{
					int n = 0;
					for (char i = 0; i < v_sub_options->at(1).name.size(); ++i)
					{
						n *= 10;
						n += v_sub_options->at(1).name.at(i) - 48;
					}
					if (n > 255)
					{
						LOG("ERROR:: number too high");
						v_sub_options->at(1).name.clear();
					}
					else
					{
						levels = static_cast<unsigned char>(n);
						v_sub_options->at(1).exists = false;
						v_sub_options->at(0).exists = false;
						levelsAll();
						showProc();
						v_sub_options->at(1).name.clear();

						v_proc_images->clear();
					}
				}
			}
		}
		if (v_filters->at(0).exists)
		{
			v_objects->at(2).exists = false;
			LOG("FILTER0 EXISTS");
			DrawObj(v_filters->at(0));
			for (char i = 1; i < v_filters->size(); ++i)
				v_filters->at(i).exists = true;
		}
		else
		{
			
			for (char i = 1; i < v_filters->size(); ++i)
				v_filters->at(i).exists = false;
		}
		for (char i = 1; i < v_filters->size(); ++i)
		{
			if (v_filters->at(i).exists)
			{
				DrawObj(v_filters->at(i));
				
				if (press(v_filters->at(i)))
				{
					switch (i)
					{
					case 1:
						GaussAll3();
						showProc();
						v_proc_images->clear();
						v_filters->at(0).exists = false;
						break;
					case 2:
						GaussAll5();
						showProc();
						v_proc_images->clear();
						v_filters->at(0).exists = false;
						break;
					case 3:
						cannyAll();
						showProc();
						v_proc_images->clear();
						v_filters->at(0).exists = false;
						break;
					case 4:
						MGall();
						showProc();
						v_proc_images->clear();
						v_filters->at(0).exists = false;
						break;
					default:
						break;
					}
				}
			}
		}



		///////////////////////////////////////////////////////
		// end draw
		glfwSwapBuffers(window);
		glFlush();
		//glDeleteBuffers(1, &VBE);
	}
	
	glfwTerminate();

}