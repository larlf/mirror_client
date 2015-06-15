#include "opengl_test.h"


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

TEST_F(Test1, test2)
{
	int argc = 0;
	char* argv = {};
	glutInit(&argc, &argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutReshapeFunc(changeSize);

	glutCreateWindow(&argv[0]);
	if (glewInit())
	{
		std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
		exit(EXIT_FAILURE);
	}

	init();

	glutDisplayFunc(display2);
	glutMainLoop();
}


void Test1::init()
{
	glGenVertexArrays(1, VAOs);
	checkGLError("glGenVertexArrays()");
	std::cout << "Num:" << 1 << std::endl;
	std::cout << "ArraySize:" << sizeof(VAOs) << std::endl;
	glBindVertexArray(VAOs[0]);
	GLfloat vertices[NumVertices][2] = {
		{ -0.90, -0.90 }, // Triangle 1
		{ 0.85, -0.90 },
		{ -0.90, 0.85 },
		{ 0.90, -0.85 }, // Triangle 2
		{ 0.90, 0.90 },
		{ -0.85, 0.90 }
	};
	glGenBuffers(1, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "../res/test.vert" },
		{ GL_FRAGMENT_SHADER, "../res/test.frag" },
		{ GL_NONE, NULL }
	};
	GLuint program = Test1::LoadShaders(shaders);
	glUseProgram(program);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
}

void Test1::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(0.25, 0.25, 0.0);
	glVertex3f(0.75, 0.25, 0.0);
	glVertex3f(0.75, 0.75, 0.0);
	glVertex3f(0.25, 0.75, 0.0);
	glEnd();

	glutSwapBuffers();
}

const GLchar* Test1::ReadShader(const char* filename)
{
	FILE* infile;
	fopen_s(&infile, filename, "rb");
	//infile=fopen("D:\\temp\\test.vert", "a");
	std::cout << "File : " << infile << std::endl;

	if (!infile) {
		std::cerr << "Unable to open file '" << filename << "'" << std::endl;
		return NULL;
	}

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	GLchar* source = new GLchar[len + 1];

	fread(source, 1, len, infile);
	fclose(infile);

	source[len] = 0;

	return const_cast<const GLchar*>(source);
}

GLuint Test1::LoadShaders(ShaderInfo* shaders)
{
	if (shaders == NULL) { return 0; }

	GLuint program = glCreateProgram();

	ShaderInfo* entry = shaders;
	while (entry->type != GL_NONE) {
		GLuint shader = glCreateShader(entry->type);

		entry->shader = shader;

		const GLchar* source = ReadShader(entry->filename);
		if (source == NULL) {
			for (entry = shaders; entry->type != GL_NONE; ++entry) {
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}

			return 0;
		}

		glShaderSource(shader, 1, &source, NULL);
		delete[] source;

		glCompileShader(shader);

		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
#ifdef _DEBUG
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			std::cerr << "Shader compilation failed: " << log << std::endl;
			delete[] log;
#endif /* DEBUG */

			return 0;
		}

		glAttachShader(program, shader);

		++entry;
	}

#ifdef GL_VERSION_4_1
	if (GLEW_VERSION_4_1) {
		// glProgramParameteri( program, GL_PROGRAM_SEPARABLE, GL_TRUE );
	}
#endif /* GL_VERSION_4_1 */

	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
#ifdef _DEBUG
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		std::cerr << "Shader linking failed: " << log << std::endl;
		delete[] log;
#endif /* DEBUG */

		for (entry = shaders; entry->type != GL_NONE; ++entry) {
			glDeleteShader(entry->shader);
			entry->shader = 0;
		}

		return 0;
	}

	return program;
}

void Test1::display2()
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[0]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

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

void Test1::changeSize(GLsizei width, GLsizei height)
{
	LOG_DEBUG("Change Size : " << width << "," << height);
}

GLuint *Test1::Buffers=new GLuint[1];

GLuint *Test1::VAOs=new GLuint[1];

