#include "sdk/def.hpp"
#include "sdk/VertexArray.hpp"
#include "sdk/VertexBuffer.hpp"
#include "sdk/BufferLayout.hpp"
#include "sdk/IndexBuffer.hpp"
#include "sdk/Shader.hpp"
#include "sdk/Camera.hpp"
#include "sdk/Controller.hpp"


static bool init(GLFWwindow*& window)
{
	if (!glfwInit())
	{
		return false;
	}

	window = glfwCreateWindow(640, 640, "Solar System", nullptr, nullptr);

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

	std::vector<float> vertexes;
	std::vector<unsigned int> indexes;
	int H = 40, V = 40;
	float R = 50.f;
	float pitchMod = 180.f / H;
	float yawMod = 360.f / V;

	// topmost point
	vertexes.push_back(0.0f);
	vertexes.push_back(R);
	vertexes.push_back(0.0f);

	for (int i = 1; i < V; i++)
	{
		for (int j = 0; j < H; j++)
		{
			float yaw = j * yawMod;
			float pitch = i * pitchMod - 90.f;
			float x = R * cosf(glm::radians(pitch)) * cosf(glm::radians(yaw));
			float y = -R * sinf(glm::radians(pitch));
			float z = R * cosf(glm::radians(pitch)) * sinf(glm::radians(yaw));
			vertexes.push_back(x);
			vertexes.push_back(y);
			vertexes.push_back(z);

			if (i == 1)
			{
				indexes.push_back(j % H);
				indexes.push_back((j + 1) % H);
				indexes.push_back(0);
			}

			if (i != V - 1)
			{
				indexes.push_back((i - 1) * H + j % H);
				indexes.push_back((i - 1) * H + (j + 1) % H);
				indexes.push_back(i * H + j % H);

				indexes.push_back(i * H + j % H);
				indexes.push_back(i * H + (j + 1) % H);
				indexes.push_back((i - 1) * H + (j + 1) % H);
			}
			else
			{
				indexes.push_back((i - 1) * H + j % H);
				indexes.push_back((i - 1) * H + (j + 1) % H);
				indexes.push_back(1 + (V - 1) * H);
			}
		}
	}

	//bottom most point
	vertexes.push_back(0.0f);
	vertexes.push_back(-R);
	vertexes.push_back(0.0f);

	VertexBuffer vb(&vertexes[0], vertexes.size() * sizeof(float));
	IndexBuffer ib(&indexes[0], indexes.size());
	BufferLayout layout;
	layout.push(GL_FLOAT, 3, GL_FALSE);
	VertexArray va(vb, ib, layout);
	Shader shader("src/shaders/shader.vert", "src/shaders/shader.frag");
	shader.enable();

	Camera camera({ 0.0f, 0.0f, 100.0f });

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.f), 640.f / 640.f, 0.1f, 1000.f);

	shader.uniformMatrix4fv("u_model", model);
	shader.uniformMatrix4fv("u_projection", projection);

	Controller::getInstance()->install(window, &camera);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.uniformMatrix4fv("u_view", camera.viewMatrix());
		va.bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		GLCall(glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr));

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	Controller::getInstance()->uninstall();

	//glfwTerminate();
	return 0;
}
