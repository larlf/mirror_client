#ifndef MM_OPENGL_H
#define MM_OPENGL_H

#include <vector>
#include <memory>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <core/mm_utils.h>

namespace mm
{
	namespace gl
	{
		//��ɫ��
		class GLShader
		{
		protected:
			virtual void compile();

		public:
			GLenum type;  //��ɫ������
			GLuint handler;  //��ɫ��
			std::string filename;  //��ɫ�����ļ�·��
			std::string text;  //��ɫ�����ļ�����

			GLShader(GLenum type, const std::string& filename);
			virtual ~GLShader();
			
		};

		class VertexShader : public GLShader
		{
		public:
			VertexShader(const std::string& filename);
		};

		//GL_FRAGMENT_SHADER
		class FragmentShader : public GLShader
		{
		public:
			FragmentShader(const std::string& filename);
		};

		class GLProgram
		{
		public:
			GLuint handler;  //���
			bool isCompiled;
			std::vector<PTR<GLShader>> shaders;  //ʹ�õ�����ɫ��

			GLProgram();
			~GLProgram();
			void attachShader(PTR<GLShader> shader);
			void compile();
		};

		class OpenGLUtils
		{
		private:
			static PTR<GLProgram> CurrentProgram;

		public:
			static void InitApp(int width, int height);
			static void useProgram(PTR<GLProgram> program);
		};
	}
}

#endif