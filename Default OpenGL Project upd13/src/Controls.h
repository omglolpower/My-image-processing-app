#pragma once
#include "opengl.h"
#include "GUI.h"
#include <iostream>
#define LOG(x) std::cout<<x<<std::endl

bool pressObj(GLFWwindow*& window, double& cursor_x, double& cursor_y, int& ww, int& hh, cRect& r2, int& LMB);
bool pressNotObj(GLFWwindow*& window, double& cursor_x, double& cursor_y, int& ww, int& hh, cRect& r2, int& LMB);