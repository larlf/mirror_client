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
		//着色器
		class GLShader
		{
		protected:
			virtual void compile();

		public:
			GLenum type;  //着色器类型
			GLuint handler;  //着色器
			std::string filename;  //着色器的文件路径
			std::string text;  //着色器的文件内容

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

		class GLProgram : public std::enable_shared_from_this<GLProgram>
		{
		private:
			static PTR<GLProgram> CurrentProgram;
			void compile();
		public:
			GLuint handler;  //句柄
			bool isCompiled;
			std::vector<PTR<GLShader>> shaders;  //使用到的着色器

			GLProgram();
			~GLProgram();
			void attachShader(PTR<GLShader> shader);
			
			//设为当前的Program
			void use();
		};

		class OpenGLUtils
		{
		public:
			static void InitApp(int width, int height);
			static int CheckError(const std::string& info);
		};
	}
}

#endif