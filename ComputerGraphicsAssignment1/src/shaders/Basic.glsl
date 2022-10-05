#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 i_color;

uniform mat4 u_mvp;

out vec4 color;

void main()
{
	gl_Position = u_mvp * vec4(pos.xyz, 1.0);

	color = vec4(i_color.xyz, 1.0);
}

#shader fragment
#version 330 core

in vec4 color;
uniform mat4 u_colorModelTransform;
out vec4 o_color;

void main()
{
	o_color = vec4((u_colorModelTransform * color).xyz, 1.0f);
}