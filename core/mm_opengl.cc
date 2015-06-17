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

mm::opengl::Shader::Shader(GLenum type, const std::string& filename) : type(type), filename(filename), shader(0)
{
	this->text = mm::FileUtils::readTextFile(filename);
}

mm::opengl::Shader::~Shader()
{

}

void mm::opengl::Shader::compile()
{
	this->shader = glCreateShader(this->type);
	const char* shaderText = this->text.c_str();
	glShaderSource(this->shader, 1, &shaderText, NULL);
	glCompileShader(shader);

	//取得编译结果
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		//取编译错误的信息
		GLsizei len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shader, len, &len, log);
		LOG_ERROR("Shader Compile Error : "<<log);
		delete[] log;
	}
}

mm::opengl::VertexShader::VertexShader(const std::string& filename) : Shader(GL_VERTEX_SHADER, filename)
{
}
