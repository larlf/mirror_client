#include <windows.h>  
#include <gl/gl.h>
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>
#include "test1.h"

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}