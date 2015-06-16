#include "mm_opengl.h"

#include <core/mm_utils.h>
#include <windows.h>  
#include <GL/glew.h>
#include <GL/freeglut.h>

void mm::OpenGLUtils::InitApp(int width, int height)
{
	int argc = 0;
	char* argv = {};
	glutInit(&argc, &argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow(&argv[0]);
	if (glewInit())
	{
		LOG_ERROR("Init GLEW Error!");
		exit(EXIT_FAILURE);
	}
}

