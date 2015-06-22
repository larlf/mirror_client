#include "opengl_test.h"
#include <core/mm_opengl.h>

using namespace mm::gl;

GLuint *Test1::Buffer1 = new GLuint[1];
GLuint *Test1::VAO1 = new GLuint[1];

TEST_F(Test1, test1)
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

	glGenVertexArrays(1, VAO1);
	OpenGLUtils::CheckError("glGenVertexArrays()");

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

void Test1::init2()
{
	GLfloat positions[] = {
		-1.0, -1.0, 0, 1,
		1, -1, 0, 1,
		1, 1, 0, 1,
		-1, 1, 0, 1
	};

	GLfloat colors[] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
		1, 1, 1
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors);


}

