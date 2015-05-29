#include <windows.h>  
#include <gl/gl.h>
#include <gtest/gtest.h>
#include "opengl_test.h"

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}