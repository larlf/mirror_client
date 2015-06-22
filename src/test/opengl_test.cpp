#include "opengl_test.h"
#include <core/mm_opengl.h>

using namespace mm::gl;

GLuint *Test1::VBO = new GLuint[1];
GLuint *Test1::VAO = new GLuint[1];

TEST_F(Test1, main)
{
	OpenGLUtils::InitApp(512, 512);
	init();
	glutDisplayFunc(display);
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

	glGenVertexArrays(1, VAO);
	OpenGLUtils::CheckError("glGenVertexArrays()");

	std::cout << "Num:" << 1 << std::endl;
	std::cout << "ArraySize:" << sizeof(VAO) << std::endl;

	glBindVertexArray(VAO[0]);
	{
		GLfloat vertices[6][2] = {
			{ -0.90, -0.90 }, // Triangle 1
			{ 0.85, -0.80 },
			{ -0.90, 0.85 },
			{ 0.90, -0.85 }, // Triangle 2
			{ 0.90, 0.90 },
			{ -0.85, 0.90 }
		};
		glGenBuffers(1, VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		PTR<GLShader> s1 = PTR<GLShader>(new VertexShader("../res/test1.vert"));
		PTR<GLShader> s2 = PTR<GLShader>(new FragmentShader("../res/test1.frag"));
		PTR<GLProgram> p1 = PTR<GLProgram>(new GLProgram());
		p1->attachShader(s1);
		p1->attachShader(s2);
		p1->use();

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}
}

void Test1::display()
{
	glClearColor(0, 0, 0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glutSwapBuffers();
}

TEST_F(Test2, main)
{
	OpenGLUtils::InitApp(512, 512);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

void Test2::init()
{

}

void Test2::display()
{

}
