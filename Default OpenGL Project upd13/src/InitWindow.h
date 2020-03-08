#pragma once
#include "opengl.h"
#include <iostream>



void frame_buffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
void initWindow( GLFWwindow*& window, const int w, const int h);