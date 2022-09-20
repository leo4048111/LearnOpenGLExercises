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
	vec3 deffuse;
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
	float specularStrength = 0.5;
	vec3 viewDir = normalize(u_viewPos - FragPos);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_lightPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
	vec3 specular = u_material.specular * spec * u_lightColor.xyz;
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = vec3(diff * u_material.deffuse * u_lightColor.xyz);
	vec3 ambient = u_material.ambient * u_lightColor.xyz;
	vec3 result = (ambient + diffuse + specular) * u_objectColor.xyz;
	color = vec4(result, 1.0);
};