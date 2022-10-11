#include "sdk/Headers.hpp"
#include "sdk/VertexArray.hpp"
#include "sdk/VertexBuffer.hpp"
#include "sdk/BufferLayout.hpp"
#include "sdk/IndexBuffer.hpp"
#include "sdk/Shader.hpp"
#include "sdk/Camera.hpp"
#include "sdk/Controller.hpp"
#include "sdk/Renderer.hpp"

#include "Helper.hpp"
#include "Planet.hpp"

const int windowWidth = 1280, windowHeight = 720;


static bool init(GLFWwindow*& window)
{
	if (!glfwInit())
	{
		return false;
	}

	window = glfwCreateWindow(windowWidth, windowHeight, "Solar System", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		return false;

	glEnable(GL_DEPTH_TEST);

	return true;
}

int main()
{
	GLFWwindow* window = nullptr;
	if (!init(window)) return 0;

	auto va = Helper::makeSphereVertexArray(90, 90, 20.f);

	auto shader = std::make_shared<Shader>("src/shaders/shader.vert", "src/shaders/shader.frag");

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.f), (float)windowWidth / windowHeight, 0.1f, 1000.f);

	Camera camera({ -100.0f, 0.0f, 0.0f }, projection);

	shader->uniformMatrix4fv("u_projection", camera.projectionMatrix());

	Controller::getInstance()->install(window, &camera);
	
	Planet center(va, shader, 100.f);
	Planet p2(va, shader, 10.f);
	Planet p3(va, shader, 1000.f);
	p2.moveTo({ 100.f, 0.f, 0.f });

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader->uniformMatrix4fv("u_view", camera.viewMatrix());

		p2.update(center.position(), center.mass(), 0.9f, 150.f);
		p3.update(p2.position(), p2.mass(), 0.7f, 70.f);
		center.draw(GL_LINE);
		p2.draw(GL_LINE);
		p3.draw(GL_LINE);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	Controller::getInstance()->uninstall();

	//glfwTerminate();
	return 0;
}
