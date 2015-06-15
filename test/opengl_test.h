#ifndef TEST1
#define TEST1

#include <windows.h>  
#include <gtest/gtest.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

typedef struct {
	GLenum       type;
	const char*  filename;
	GLuint       shader;
} ShaderInfo;

#define BUFFER_OFFSET(x)  ((const void*) (x))

class Test1 : public testing::Test
{
public:
	static GLuint *VAO1;
	static GLuint *VAO2;
	static GLuint *Buffer1;
	static GLuint *Buffer2;

	static const GLchar* ReadShader(const char* filename);
	static GLuint LoadShaders(ShaderInfo* shaders);

	static void init();
	static void display();
	static void display2();
};


#endif