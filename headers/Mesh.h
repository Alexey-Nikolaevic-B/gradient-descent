//---------------------------------------------------------
//	DESCRIPTION: Creates tringle and shaderProgram(for now) // TODO: Fix description
//---------------------------------------------------------

#ifndef MESH_H
#define MESH_H


#include <vector>

#include "Shader.h"
#include "Camera.h"

class Mesh
{
public:
	~Mesh();

	void Initialize(std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices);

	void DrawPoint(Shader& meshShader, Camera& camera);
	void DrawLine(Shader& meshShader, Camera& camera);
	void DrawTriangle(Shader& meshShader, Camera& camera, std::vector<glm::vec3>& vertices);

private:
	GLuint VAO, VBO, EBO;
	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;
};

#endif