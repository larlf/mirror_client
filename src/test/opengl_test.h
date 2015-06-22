#ifndef TEST1
#define TEST1

#include <windows.h>  
#include <gtest/gtest.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <core/mm_utils.h>

class Test1 : public testing::Test
{
public:
	static GLuint *VAO;
	static GLuint *VBO;

	static void init();
	static void display();
};

class Test2 : public testing::Test
{
public:
	static GLuint vao[];
	static GLuint vbo[];
	static GLuint ebo[];

	static void init();
	static void display();
};


#endif