#ifndef TEST1
#define TEST1

#include <windows.h>  
#include <gl/gl.h>
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>
#include <GL/freeglut.h>

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

class Test1 : public testing::Test
{
public:
	static void init();
	static void display();
};


#endif