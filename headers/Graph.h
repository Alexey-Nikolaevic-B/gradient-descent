//--------------------------------------------------------------
//	DESCRIPTION: Compiles graph
//--------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H


#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Function.h"

class Graph
{
public:
	void Initialize(GLFWwindow* window, float scale, float resolution, glm::vec4 boundaries);

	void Draw(Shader& meshShader, Shader& netShader, Camera& camera);

private:
	GLFWwindow* window;
	Mesh plane;
	Mesh net;

	float scale;
	float resolution;
	glm::vec4 boundaries;

	std::vector<glm::vec3> planeVertices;
	std::vector<GLuint> planeIndices;

	std::vector<glm::vec3> netVertices;
	std::vector<GLuint> netIndices;

	float function(float x, float z);

	std::vector<glm::vec3>& GenerateVertices();

	std::vector<GLuint>& GeneratePointIndices();
	std::vector<GLuint>& GenerateLineIndices();

	std::vector<glm::vec3>& GenerateNetVertices();
	std::vector<GLuint>& GenerateNetIndices();
};

#endif