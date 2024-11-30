//---------------------------------------------------------
//	DESCRIPTION: Compiles whole application
//---------------------------------------------------------

#ifndef APPLICATION_H
#define APPLICATION_H


#include "IWindow.h"
#include "Shader.h"
#include "Camera.h"
#include "Graph.h"
#include "GradientDescent.h"

class Application
{
public:
	Application();

	void Run();

	void Program_State_Descent(GLFWwindow* window);
	void Program_State_Graph(GLFWwindow* window);

	void CheckForExit(GLFWwindow* window);

private:
	IWindow iwindow;

	Shader planeShader;
	Shader netShader;
	Shader arrowShader;

	Camera camera;

	Graph graph;
};

#endif

