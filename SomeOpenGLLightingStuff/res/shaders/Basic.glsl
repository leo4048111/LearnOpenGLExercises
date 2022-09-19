#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(aPosition.xyz, 1.0);
	Normal = mat3(transpose(inverse(u_model))) * aNormal;
	FragPos = vec3(u_model * vec4(aPosition.xyz, 1.0));
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_objectColor;
uniform vec4 u_lightColor;

uniform vec3 u_lightPos;
in vec3 Normal;
in vec3 FragPos;

void main()
{
	float ambientStrength = 0.1;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = vec3(diff * u_lightColor);
	vec3 ambient = ambientStrength * u_lightColor.xyz;
	vec3 result = (ambient + diffuse) * u_objectColor.xyz;
	color = vec4(result, 1.0);
};