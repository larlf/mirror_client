#ifndef MM_OPENGL_H
#define MM_OPENGL_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <core/mm_utils.h>

namespace mm
{
	namespace opengl
	{
		//��ɫ��
		class Shader
		{
		public:
			GLenum type;  //��ɫ������
			GLuint shader;  //��ɫ��
			std::string filename;  //��ɫ�����ļ�·��
			std::string text;  //��ɫ�����ļ�����

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