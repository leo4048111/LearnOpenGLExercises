#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

out vec4 v_color;
out vec2 texCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(aPosition.x, -aPosition.y, aPosition.z, 1.0);
	v_color = gl_Position;
	texCoord = aTexCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_myColor;
in vec4 v_color;
in vec2 texCoord;
uniform float u_visibility;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main()
{
	color = mix(texture(u_texture1, texCoord), texture(u_texture2, texCoord), u_visibility);
};