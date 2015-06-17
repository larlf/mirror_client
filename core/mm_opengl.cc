#include "mm_opengl.h"

#include <core/mm_utils.h>
#include <windows.h>

void mm::gl::OpenGLUtils::InitApp(int width, int height)
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

mm::gl::GLShader::GLShader(GLenum type, const std::string& filename) : type(type), filename(filename), handler(0)
{
	this->text = mm::FileUtils::readTextFile(filename);
	this->handler = glCreateShader(this->type);
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

		//ȡ�ñ�����
		GLint compiled;
		glGetShaderiv(handler, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			//ȡ����������Ϣ
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

mm::gl::GLProgram::GLProgram() : handler(0), isCompiled(false)
{
	this->handler = glCreateProgram();
}

mm::gl::GLProgram::~GLProgram()
{
	this->shaders.clear();
	glDeleteProgram(this->handler);
}

void mm::gl::GLProgram::attachShader(std::shared_ptr<GLShader> shader)
{
	this->shaders.push_back(shader);
	glAttachShader(this->handler, shader->handler);
}

void mm::gl::GLProgram::compile()
{

}
