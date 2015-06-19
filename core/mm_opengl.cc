#include "mm_opengl.h"

#include <core/mm_utils.h>
#include <windows.h>

PTR<mm::gl::GLProgram> mm::gl::GLProgram::CurrentProgram;

void mm::gl::OpenGLUtils::InitApp(int width, int height)
{
	int argc = 0;
	char* argv = {};
	glutInit(&argc, &argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutCreateWindow(&argv[0]);
	if (glewInit())
	{
		LOG_ERROR("Init GLEW Error!");
		exit(EXIT_FAILURE);
	}
}

int mm::gl::OpenGLUtils::CheckError(const std::string& info)
{
	GLenum errorNum;
	int errorCount = 0;
	while ((errorNum = glGetError()) != GL_NO_ERROR)
	{
		errorCount++;
		char* msg = (char*)gluErrorString(errorNum);
		LOG_ERROR("OpenGL Error : " << msg << " @ " << info);
	}

	return errorCount;
}

mm::gl::GLShader::GLShader(GLenum type, const std::string& filename) : type(type), filename(filename), handler(0)
{
	this->text = mm::FileUtils::readTextFile(filename);
	this->handler = glCreateShader(this->type);

	this->compile();
}

mm::gl::GLShader::~GLShader()
{
	if (this->handler)
	{
		glDeleteShader(this->handler);
		this->handler = 0;
	}
}

void mm::gl::GLShader::compile()
{
	if (this->text.size() > 0)
	{
		const char* shaderText = this->text.c_str();
		glShaderSource(this->handler, 1, &shaderText, NULL);
		glCompileShader(handler);

		//取得编译结果
		GLint compiled;
		glGetShaderiv(handler, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			//取编译错误的信息
			GLsizei len;
			glGetShaderiv(handler, GL_INFO_LOG_LENGTH, &len);
			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(handler, len, &len, log);
			LOG_ERROR("Shader Compile Error : "<<log);
			delete[] log;
		}
	}
}

mm::gl::VertexShader::VertexShader(const std::string& filename) : GLShader(GL_VERTEX_SHADER, filename)
{
}

mm::gl::FragmentShader::FragmentShader(const std::string& filename) : GLShader(GL_FRAGMENT_SHADER, filename)
{

}

mm::gl::GLProgram::GLProgram() : isCompiled(false)
{
	this->handler = glCreateProgram();
}

mm::gl::GLProgram::~GLProgram()
{
	this->shaders.clear();
	glDeleteProgram(this->handler);
}

void mm::gl::GLProgram::attachShader(PTR<GLShader> shader)
{
	this->shaders.push_back(shader);
	glAttachShader(this->handler, shader->handler);
}

void mm::gl::GLProgram::compile()
{
	if (!this->isCompiled)
	{
		//连接程序
		glLinkProgram(this->handler);

		//检查是否连接成功
		GLint linked;
		glGetProgramiv(this->handler, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLsizei len;
			glGetProgramiv(this->handler, GL_INFO_LOG_LENGTH, &len);
			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(this->handler, len, &len, log);
			LOG_ERROR("GLProgram Compile Error : " << log);
			delete[] log;
		}
		else
		{
			//编译成功
			this->isCompiled = true;
		}
	}
}

void mm::gl::GLProgram::use()
{
	this->compile();

	//锁定并使用Program
	GLProgram::CurrentProgram = this->shared_from_this();
	glUseProgram(this->handler);
}
