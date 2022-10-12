#include "sdk/Camera.hpp"
#include "sdk/Controller.hpp"

#include "World.hpp"

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

	// init camera
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.f), (float)windowWidth / windowHeight, 0.1f, 1000.f);
	Camera camera({ -100.0f, 0.0f, 0.0f }, projection);

	// init shader
	auto shader = std::make_shared<Shader>("src/shaders/shader.vert", "src/shaders/shader.frag");
	shader->uniformMatrix4fv("u_projection", camera.projectionMatrix());

	// install controller
	Controller::getInstance()->install(window, &camera);

	// attribs of 8 planets + sun + moon
	float sunMass = 333400.f, mercuryMass = 1.f, venusMass = 1.f, earthMass = 4000.f, moonMass = 1.f, marsMass = 1.f, jupiterMass = 1.f, saturnMass = 1.f, uranusMass = 1.f, neptuneMass = 1.f, plutoMass = 1.f;
	float mercuryE = 0.6f, venusE = 0.65f, earthE = 0.7f, moonE = 0.7f, marsE = 0.72f, jupiterE = 0.75f, saturnE = 0.79f, uranusE = 0.81f, neptuneE = 0.83f, plutoE = 0.85f;
	float mercuryFD = 30.f, venusFD = 60.f, earthFD = 100.f, moonFD = 40.f, marsFD = 140.f, jupiterFD = 170.f, saturnFD = 200.f, uranusFD = 230.f, neptuneFD = 260.f, plutoFD = 300.f;
	glm::vec3 sunScale = { 1.0f, 1.0f, 1.0f }, mercuryScale = { 0.2f, 0.2f, 0.2f }, venusScale = { 0.3f, 0.3f, 0.3f }, earthScale = { 0.5f, 0.5f, 0.5f }, moonScale = { 0.1f, 0.1f, 0.1f };
	glm::vec3 marsScale = { 0.28f, 0.28f, 0.28f }, jupiterScale = { 0.7f, 0.7f, 0.7f }, saturnScale = { 0.65f, 0.65f, 0.65f }, uranusScale = { 0.38f, 0.38f, 0.38f }, neptuneScale = { 0.38f, 0.38f, 0.38f };
	glm::vec3 plutoScale = { 0.2f, 0.2f, 0.2f };
	glm::vec4 sunColor = { 1.0f, 0.0f, 0.0f, 1.0f }, mercuryColor = { 0.75f, 0.45f, 0.13f, 1.0f }, venusColor = {0.55f, 0.44f, 0.27f, 1.0f}, earthColor = { 0.0f, 0.0f, 1.0f, 1.0f }, moonColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec4 marsColor = { 0.73f, 0.33f, 0.23, 1.0f }, jupiterColor = { 0.57f, 0.40f, 0.25, 1.0f }, saturnColor = { 0.89f, 0.71f, 0.49f, 1.0f }, uranusColor = { 0.16f,0.75f, 0.93f, 1.0f }, neptuneColor = { 0.16f,0.75f, 0.93f, 1.0f };
	glm::vec4 plutoColor = { 0.46f, 0.67f, 0.71f, 1.0f };

	//init world
	g_world->init(50, 50, 20.f);
	g_world->addPlanet("sun", "sun", 1.0f, 0.0f, shader, sunMass, { 0.0f, 0.0f, 0.0f }, sunScale, sunColor);
	g_world->addPlanet("mercury", "sun", mercuryE, mercuryFD, shader, mercuryMass, { mercuryFD, 0.0f, 0.0f }, mercuryScale, mercuryColor);
	g_world->addPlanet("venus", "sun", venusE, venusFD, shader, venusMass, { venusFD, 0.0f, 0.0f }, venusScale, venusColor);
	g_world->addPlanet("earth", "sun", earthE, earthFD, shader, earthMass, { earthFD, 0.0f, 0.0f }, earthScale, earthColor);
	g_world->addPlanet("moon", "earth", moonE, moonFD, shader, moonMass, { moonFD, 0.0f, 0.0f }, moonScale, moonColor);
	g_world->addPlanet("mars", "sun", marsE, marsFD, shader, marsMass, { marsFD, 0.0f, 0.0f }, marsScale, marsColor);
	g_world->addPlanet("jupiter", "sun", jupiterE, jupiterFD, shader, jupiterMass, { jupiterFD, 0.0f, 0.0f }, jupiterScale, jupiterColor);
	g_world->addPlanet("saturn", "sun", saturnE, saturnFD, shader, saturnMass, { saturnFD, 0.0f, 0.0f }, saturnScale, saturnColor);
	g_world->addPlanet("uranus", "sun", uranusE, uranusFD, shader, uranusMass, { uranusFD, 0.0f, 0.0f }, uranusScale, uranusColor);
	g_world->addPlanet("neptune", "sun", neptuneE, neptuneFD, shader, neptuneMass, { neptuneFD, 0.0f, 0.0f }, neptuneScale, neptuneColor);
	g_world->addPlanet("pluto", "sun", plutoE, plutoFD, shader, plutoMass, { plutoFD, 0.0f, 0.0f }, plutoScale, plutoColor);


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader->uniformMatrix4fv("u_view", camera.viewMatrix());

		g_world->draw(GL_LINE);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	Controller::getInstance()->uninstall();

	//glfwTerminate();
	return 0;
}
