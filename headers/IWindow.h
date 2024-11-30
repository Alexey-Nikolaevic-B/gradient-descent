//---------------------------------------------------------
//	DESCRIPTION: Initializes GLFW and Window, makes Window
//	current context
//---------------------------------------------------------

#ifndef IWINDOW_H
#define IWINDOW_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>

class IWindow
{
public:
	~IWindow();
	void Initialize(const int width, const int height, const std::string title, int version, float interval);

	GLFWwindow* getWindow()
	{
		return window;
	}

	std::string Info(glm::vec3 camPosition, std::string additionalInfo);

private:
	GLFWwindow* window = nullptr;

	//============INFO============//
	double crntTime = 0.0;
	double prevTime = 0.0;
	int c = 0;
	std::string title;
	std::string FPS;
	std::string Position;
	//===========================//
};

#endif 
