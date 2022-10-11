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

	auto va = Helper::makeSphereVertexArray(10, 10, 50.f);

	auto shader = std::make_shared<Shader>("src/shaders/shader.vert", "src/shaders/shader.frag");

	Planet planet(va, shader);
	Planet planet2(va, shader);
	planet2.moveTo({ 0.0f, 0.0f, 0.0f });

	Camera camera({ 0.0f, 0.0f, 100.0f });

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.f), (float)windowWidth / windowHeight, 0.1f, 1000.f);

	shader->uniformMatrix4fv("u_projection", projection);

	Controller::getInstance()->install(window, &camera);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader->uniformMatrix4fv("u_view", camera.viewMatrix());
		planet2.draw(GL_LINE);
		auto degree = 100* glfwGetTime();
		planet.moveTo({ 150.f * cosf(glm::radians(degree)), 0.0f, 150.f * sinf(glm::radians(degree)) });
		planet.draw(GL_LINE);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	Controller::getInstance()->uninstall();

	//glfwTerminate();
	return 0;
}
