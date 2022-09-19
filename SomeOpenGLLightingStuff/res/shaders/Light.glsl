#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;

uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * vec4(aPosition.xyz, 1.0f);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
};