#include "Application.h"


//============================Config===============================//
//Window:
const int WIDTH =			1200;
const int HEIGHT =			800;
const std::string TITLE =	"Project1";
const int OPENGL_VERSION =	3;
const float SWAP_INTERAVL =	1.0f;

//Camera:
const glm::vec3 CAMERA_START_POSITION =		glm::vec3(18.0f, 12.0f, 18.0f);
const glm::vec3 CAMERA_START_ORIENTATION =	glm::vec3(-1.0f, -0.8f, -1.0f);
const float NEAR_RENDER_DISTANCE =			2.0f;
const float FAR_RENDER_DISTANCE =			50.0f;
const float FIELD_OF_VIEW =					45.0f;
const float CAMERA_SPEED =					0.05f;
const float MOUSE_SENSITIVITY =				50.0f;

//Shader:
const std::string MESH_DEFAULT_VERT_FILE =	"Source/Shaders/Mesh_default.vert";
const std::string MESH_DEFAULT_FRAG_FILE =	"Source/Shaders/Mesh_default.frag";
const std::string SIMPLE_COLOR_FRAG_FILE =	"Source/Shaders/Simple_Color.frag";
const std::string ARROW_FILE =				"Source/Shaders/Arrow.frag";

//Function:
const float SCALE =				15;
const float RESOLUTION =		150;
const glm::vec4 BOUNDARIES =	glm::vec4(-12.0f, 12.0f, -12.0f, 12.0f); // (x1;x2 : y1;y2)

//GradientDescent:
const int	NUMBER_OF_ARROWS =		100;
const int NUMBER_OF_ITERATIONS =	1500;
const float MIN_GRAD_VECTOR =		0.001f;
const float ARROW_STEP =			0.03f;

//BackGroundColor:
const GLfloat CLEARCOLOR[]{0.15f, 0.15f, 0.15f, 1.0f};
//=================================================================//


Application::Application()
{
	iwindow.Initialize(WIDTH, HEIGHT, TITLE, OPENGL_VERSION, SWAP_INTERAVL);

	planeShader.Initialize(MESH_DEFAULT_VERT_FILE, MESH_DEFAULT_FRAG_FILE);
	netShader.Initialize(MESH_DEFAULT_VERT_FILE, SIMPLE_COLOR_FRAG_FILE);
	arrowShader.Initialize(MESH_DEFAULT_VERT_FILE, ARROW_FILE);

	camera.Initialize(WIDTH, HEIGHT, CAMERA_START_POSITION, CAMERA_START_ORIENTATION, NEAR_RENDER_DISTANCE, FAR_RENDER_DISTANCE, FIELD_OF_VIEW, CAMERA_SPEED, MOUSE_SENSITIVITY);

	graph.Initialize(iwindow.getWindow(), SCALE, RESOLUTION, BOUNDARIES);
}

void Application::Run()
{	
	GLFWwindow* window = iwindow.getWindow();

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		Program_State_Graph(window);
		Program_State_Descent(window);
	}
 }

void Application::Program_State_Descent(GLFWwindow* window)
{
	GradientDescent gradientDescent;
	gradientDescent.Initialize(SCALE, BOUNDARIES, NUMBER_OF_ARROWS, NUMBER_OF_ITERATIONS, MIN_GRAD_VECTOR, ARROW_STEP);
	int counter = 0;
	std::string minInfo = " ";
	while (glfwGetKey(window, GLFW_KEY_K) != GLFW_PRESS && !glfwWindowShouldClose(window))
	{
		if (counter < NUMBER_OF_ARROWS)
		{
			gradientDescent.GenerateArrows();
			counter++;
		}

		glClearColor(CLEARCOLOR[0], CLEARCOLOR[1], CLEARCOLOR[2], CLEARCOLOR[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec2 position = gradientDescent.FindMinimum();
		minInfo = "Minimum: (" + std::to_string(round(position[0] * 1000) / 1000) + "; " + std::to_string(round(position[1] * 1000) / 1000) + ")";
		minInfo += " = " + std::to_string(Function(position[0], position[1]));
		glfwSetWindowTitle(window, iwindow.Info(camera.GetPosition(), minInfo).c_str());
		camera.Controls(window);

		graph.Draw(planeShader, netShader, camera);

		gradientDescent.Draw(arrowShader, camera);

		CheckForExit(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::Program_State_Graph(GLFWwindow* window)
{
	while (glfwGetKey(window, GLFW_KEY_L) != GLFW_PRESS && !glfwWindowShouldClose(window))
	{
		glClearColor(CLEARCOLOR[0], CLEARCOLOR[1], CLEARCOLOR[2], CLEARCOLOR[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSetWindowTitle(window, iwindow.Info(camera.GetPosition(), "").c_str());

		camera.Controls(window);

		graph.Draw(planeShader, netShader, camera);
		CheckForExit(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::CheckForExit(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		exit;
	}
}