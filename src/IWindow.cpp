#include "IWindow.h"

IWindow::~IWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void IWindow::Initialize(const int width, const int height, const std::string title, int version, float interval)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);

	glfwSwapInterval(interval);
}

std::string IWindow::Info(glm::vec3 camPosition, std::string additionalInfo)
{
	crntTime = glfwGetTime();
	c++;
	if (crntTime - prevTime >= 1.0 / 20.0)
	{
		FPS = "FPS: " + std::to_string(c / (crntTime - prevTime));
		Position = "Position: (" + std::to_string(camPosition.x) + "; " + std::to_string(camPosition.y) + "; " + std::to_string(camPosition.z) + ")";
		title = FPS + "     " + Position + "     " + additionalInfo ;
		prevTime = crntTime;
		c = 0;
	}
	return title;
}