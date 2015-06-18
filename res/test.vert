#version 430 core

layout(location=0) in vec4 vPosition;

out gl_PerVertex
{
	vec4  gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

void main()
{
	gl_Position=vPosition;
	gl_Position.x+=0.2;
}
