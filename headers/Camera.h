//--------------------------------------------------------------
//	DESCRIPTION: Transforms coordinates to screen coordinates
//--------------------------------------------------------------

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera
{
public: 

	void Initialize(int width, int height, glm::vec3 Position, glm::vec3 Orientation, float nearRenderDistance, float farRenderDistance, float FOV, float speed, float sensitivity);

	void UniformMatrix(GLuint& shaderProgram, const char* uniform);
	void Controls(GLFWwindow* window);

	glm::vec3 GetPosition();

private:
	glm::vec3 StartPosition;
	glm::vec3 Position;
	glm::vec3 StartOrientation;
	glm::vec3 Orientation;
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	int width;
	int height;

	float speed;
	float sensitivity;

	float nearRenderDistance;
	float farRenderDistance;

	float FOV;


	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	bool catchMouse = false;
	bool firstClick = true;
};

#endif