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

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

layout(location = 0) out vec4 color;

uniform vec4 u_objectColor;
uniform vec4 u_lightColor;

uniform Material u_material;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;
in vec3 Normal;
in vec3 FragPos;

void main()
{
	// 环境光
	vec3 ambient = u_lightColor.xyz * u_material.ambient;

	// 漫反射
	vec3 diffuse = u_lightColor.xyz * max(dot(normalize(Normal), normalize(u_lightPos - FragPos)), 0.0) * u_material.diffuse;

	// 镜面反射
	vec3 specular = u_lightColor.xyz * pow(max(dot(normalize(u_viewPos - FragPos), normalize(Normal)), 0.0), u_material.shininess) * u_material.specular;
	vec3 result = (ambient + diffuse + specular) * u_objectColor.xyz;
	color = vec4(result, 1.0);
};