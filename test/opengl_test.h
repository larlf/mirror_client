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

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

const GLuint NumVertices = 6;

class Test1 : public testing::Test
{
public:
	static GLuint *VAOs;
	static GLuint *Buffers;

	static const GLchar* ReadShader(const char* filename);
	static GLuint LoadShaders(ShaderInfo* shaders);

	static void init();
	static void display();
	static void display2();
};


#endif