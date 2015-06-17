#ifndef MM_OPENGL_H
#define MM_OPENGL_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <core/mm_utils.h>

namespace mm
{
	namespace opengl
	{
		//着色器
		class Shader
		{
		public:
			GLenum type;  //着色器类型
			GLuint shader;  //着色器
			std::string filename;  //着色器的文件路径
			std::string text;  //着色器的文件内容

			Shader(GLenum type, const std::string& filename);
			virtual ~Shader();
			virtual void compile();
		};

		class VertexShader : public Shader
		{
		public:
			VertexShader(const std::string& filename);
		};

		class OpenGLUtils
		{
		public:
			static void InitApp(int width, int height);
		};
	}
}

#endif