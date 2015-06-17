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
		class GLShader
		{
		public:
			GLenum type;  //��ɫ������
			GLuint handler;  //��ɫ��
			std::string filename;  //��ɫ�����ļ�·��
			std::string text;  //��ɫ�����ļ�����

			GLShader(GLenum type, const std::string& filename);
			virtual ~GLShader();
			virtual void compile();
		};

		class VertexShader : public GLShader
		{
		public:
			VertexShader(const std::string& filename);
		};

		class GLProgram
		{
		public:
			GLuint handler;  //���

			GLProgram();
			~GLProgram();
			void compile();
		};

		class OpenGLUtils
		{
		public:
			static void InitApp(int width, int height);
		};
	}
}

#endif