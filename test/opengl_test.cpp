#include "opengl_test.h"
#include <core/mm_opengl.h>

using namespace mm::gl;

//TEST_F(Test1, test1)
//{
//	int argc = 0;
//	char* argv = {};
//	glutInit(&argc, &argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//	glutInitWindowSize(800, 600);
//	glutInitWindowPosition(100, 100);
//	//glutInitContextVersion(4, 3);
//	//glutInitContextProfile(GLUT_CORE_PROFILE);
//	glutCreateWindow("Test");
//
//	Test1::init();
//
//	glutDisplayFunc(Test1::display);
//	glutMainLoop();
//}

TEST_F(Test1, test1)
{
	mm::gl:: OpenGLUtils::InitApp(512, 512);

	glutReshapeFunc(Test1::onResize);

	init();

	glutDisplayFunc(Test1::display);
	glutMainLoop();
}


void Test1::init()
{
	const GLubyte* byteGlVersion = glGetString(GL_VERSION);
	const GLubyte* byteGlVendor = glGetString(GL_VENDOR);
	const GLubyte* byteGlRenderer = glGetString(GL_RENDERER);
	const GLubyte* byteSLVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "OpenGL version: " << byteGlVersion << std::endl;
	std::cout << "GL_VENDOR: " << byteGlVendor << std::endl;
	std::cout << "GL_RENDERER: " << byteGlRenderer << std::endl;
	std::cout << "GLSL version: " << byteSLVersion << std::endl;

	glGenVertexArrays(1, VAO1);
	glGenVertexArrays(10, VAO2);
	checkGLError("glGenVertexArrays()");

	std::cout << "Num:" << 1 << std::endl;
	std::cout << "ArraySize:" << sizeof(VAO1) << std::endl;

	glBindVertexArray(VAO1[0]);
	{
		GLfloat vertices[6][2] = {
			{ -0.90, -0.90 }, // Triangle 1
			{ 0.85, -0.80 },
			{ -0.90, 0.85 },
			{ 0.90, -0.85 }, // Triangle 2
			{ 0.90, 0.90 },
			{ -0.85, 0.90 }
		};
		glGenBuffers(1, Buffer1);
		glBindBuffer(GL_ARRAY_BUFFER, Buffer1[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		PTR<GLShader> s1 = PTR<GLShader>(new VertexShader("../res/test.vert"));
		PTR<GLShader> s2 = PTR<GLShader>(new FragmentShader("../res/test.frag"));
		PTR<GLProgram> p1 = PTR<GLProgram>(new GLProgram());
		p1->attachShader(s1);
		p1->attachShader(s2);
		p1->use();

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
	}
}

void Test1::display()
{
	glClearColor(0, 0, 0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAO1[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glutSwapBuffers();
}

void Test1::checkGLError(const std::string& info)
{
	GLenum errorNum;
	while ((errorNum = glGetError()) != GL_NO_ERROR)
	{
		char* msg = (char*)gluErrorString(errorNum);
		std::cout << "Error : " << msg << " @ " << info << std::endl;
	}
}

void Test1::onResize(GLsizei width, GLsizei height)
{
	LOG_DEBUG("Change Size : " << width << "," << height);
	glViewport(0, 0, width, height);
}

GLuint * Test1::Buffer2=new GLuint[10];
GLuint * Test1::VAO2 = new GLuint[10];
GLuint *Test1::Buffer1=new GLuint[1];
GLuint *Test1::VAO1=new GLuint[1];
