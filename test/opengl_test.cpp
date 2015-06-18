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

TEST_F(Test1, test2)
{
	mm::gl:: OpenGLUtils::InitApp(512, 512);

	glutReshapeFunc(changeSize);

	init();

	glutDisplayFunc(display2);
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
		p1->compile();
		OpenGLUtils::useProgram(p1);

		/*
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "../res/test.vert" },
			{ GL_FRAGMENT_SHADER, "../res/test.frag" },
			{ GL_NONE, NULL }
		};

		//应用program
		GLuint program = Test1::LoadShaders(shaders);
		glUseProgram(program);
		*/

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
	}
}

void Test1::display2()
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAO1[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glutSwapBuffers();
}

void Test1::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	std::cout << "run..." << std::endl;

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
	while (entry->type != GL_NONE) 
	{
		GLuint shader = glCreateShader(entry->type);

		entry->shader = shader;

		//读取渲染器，并进行错误处理
		const GLchar* source = ReadShader(entry->filename);
		if (source == NULL) 
		{
			for (entry = shaders; entry->type != GL_NONE; ++entry) 
			{
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}
			return 0;
		}

		//读取代码
		glShaderSource(shader, 1, &source, NULL);
		delete[] source;

		//编译
		glCompileShader(shader);

		//取得编译结果
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) 
		{
#ifdef _DEBUG
			//取编译错误的信息
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			std::cerr << "Shader compilation failed: " << log << std::endl;
			delete[] log;
#endif
			return 0;
		}

		//关联到program
		glAttachShader(program, shader);

		++entry;
	}

#ifdef GL_VERSION_4_1
	if (GLEW_VERSION_4_1) 
	{
		glProgramParameteri( program, GL_PROGRAM_SEPARABLE, GL_TRUE );
	}
#endif

	//连接程序
	glLinkProgram(program);

	//检查是否连接成功
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) 
	{
#ifdef _DEBUG
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		std::cerr << "Shader linking failed: " << log << std::endl;
		delete[] log;
#endif

		//如果没有连接成功，销毁资源
		for (entry = shaders; entry->type != GL_NONE; ++entry) 
		{
			glDeleteShader(entry->shader);
			entry->shader = 0;
		}

		return 0;
	}

	return program;
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
	glViewport(0, 0, width, height);
}

GLuint * Test1::Buffer2=new GLuint[10];
GLuint * Test1::VAO2 = new GLuint[10];
GLuint *Test1::Buffer1=new GLuint[1];
GLuint *Test1::VAO1=new GLuint[1];
