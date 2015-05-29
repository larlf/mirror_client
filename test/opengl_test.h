#ifndef TEST1
#define TEST1

#include <windows.h>  
#include <gl/gl.h>
#include <gtest/gtest.h>
#include <GL/freeglut.h>

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


class Test1 : public testing::Test
{
public:
	static void init();
	static void display();
};


#endif