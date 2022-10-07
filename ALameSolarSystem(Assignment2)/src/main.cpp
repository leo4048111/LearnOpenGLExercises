#include "def.hpp"

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "BufferLayout.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

static bool init(GLFWwindow*& window)
{
	if (!glfwInit())
	{
		return false;
	}

	window = glfwCreateWindow(640, 480, "Solar System", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	return true;
}

int main()
{
	GLFWwindow* window = nullptr;
	if (!init(window)) return 0;

	float coords[] = {
		-0.5, -0.5,
		0.5, -0.5,
		0.5, 0.5,
		-0.5, -0.5,
		0.5, 0.5,
		-0.5, 0.5
	};

	VertexBuffer vb(coords, sizeof(coords));
	BufferLayout layout;
	layout.push(GL_FLOAT, 2, GL_FALSE);
	VertexArray va(vb, layout);
	va.bind();
	Shader shader("src/shaders/shader.vert", "src/shaders/shader.frag");
	shader.enable();

	Camera camera({ 0.0f, 0.0f, 1.0f });

	glm::mat4 model(1.0f);
	//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 projection(1.0f);
	//projection = glm::ortho(-100.f, 100.f, -100.f, 100.f, -100.f, 100.f);

	shader.uniformMatrix4fv("u_model", model);
	shader.uniformMatrix4fv("u_projection", projection);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(255, 255, 0, 255);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.uniformMatrix4fv("u_view", camera.viewMatrix());

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
