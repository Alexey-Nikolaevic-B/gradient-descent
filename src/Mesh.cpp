#include "Mesh.h"

Mesh::~Mesh()
{
	vertices.clear();
	indices.clear();
	vertices.shrink_to_fit();
	indices.shrink_to_fit();
}

void Mesh::Initialize(std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::DrawLine(Shader& meshShader, Camera& camera)
{
	meshShader.Use();
	camera.UniformMatrix(meshShader.GetShaderProgram(), "camMatrix");

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
}


void Mesh::DrawTriangle(Shader& meshShader, Camera& camera, std::vector<glm::vec3>& newVertices)
{
	meshShader.Use();
	camera.UniformMatrix(meshShader.GetShaderProgram(), "camMatrix");

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, newVertices.size() * sizeof(glm::vec3), newVertices.data(), GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}