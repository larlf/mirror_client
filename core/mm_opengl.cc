#include "mm_opengl.h"

#include <core/mm_utils.h>
#include <windows.h>

void mm::opengl::OpenGLUtils::InitApp(int width, int height)
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

mm::opengl::GLShader::GLShader(GLenum type, const std::string& filename) : type(type), filename(filename), handler(0)
{
	this->text = mm::FileUtils::readTextFile(filename);
	this->handler = glCreateShader(this->type);
}

mm::opengl::GLShader::~GLShader()
{
	if (this->handler)
	{
		glDeleteShader(this->handler);
		this->handler = 0;
	}
}

void mm::opengl::GLShader::compile()
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

mm::opengl::VertexShader::VertexShader(const std::string& filename) : GLShader(GL_VERTEX_SHADER, filename)
{
}

mm::opengl::GLProgram::GLProgram()
{
	this->handler = glCreateProgram();
}

mm::opengl::GLProgram::~GLProgram()
{

}
