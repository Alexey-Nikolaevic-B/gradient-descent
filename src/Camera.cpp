#include "Camera.h"

void Camera::Initialize(int width, int height, glm::vec3 Position, glm::vec3 Orientation, float nearRenderDistance, float farRenderDistance, float FOV, float speed, float sensitivity)
{
	Camera::width = width;
	Camera::height = height;
	Camera::StartPosition = Position;
	Camera::Position = Position;
	Camera::StartOrientation = Orientation;
	Camera::Orientation = Orientation;
	Camera::nearRenderDistance = nearRenderDistance;
	Camera::farRenderDistance = farRenderDistance;
	Camera::FOV = FOV;
	Camera::speed = speed;
	Camera::sensitivity = sensitivity;
}

void Camera::UniformMatrix(GLuint& shaderProgram, const char* uniform)
{ 
	proj = glm::perspective(glm::radians(FOV), (float)width / height, nearRenderDistance, farRenderDistance);

	view = glm::lookAt(Position, Position + Orientation, Up);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, glm::value_ptr(proj * view));
}


void Camera::Controls(GLFWwindow* window)
{
	//===============================Movement============================//
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	//===================================================================//

	//================================Utility================================//
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		Position = StartPosition;
		Orientation = StartOrientation;
	}

	//==============================CheckForClick============================//
	if (firstClick == true and glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		firstClick = false;
		catchMouse = !catchMouse;
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	if (firstClick == false and glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
	{
		firstClick = true;
	}
	//=======================================================================//
	//=======================================================================//


	//=============================MouseInput================================//

	if (catchMouse)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		Orientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	//=======================================================================//
}

glm::vec3 Camera::GetPosition()
{
	return Position;
}