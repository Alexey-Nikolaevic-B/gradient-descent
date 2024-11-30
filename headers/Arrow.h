//--------------------------------------------------------------
//	DESCRIPTION: Visualize gradient descent
//--------------------------------------------------------------

#ifndef ARROW_H
#define ARROW_H

#include "Mesh.h"
#include "Function.h"

class Arrow
{
public:
	Arrow(float scale, glm::vec4 boundaries, float min_grad_vector, float arrow_step, int numberOfIterations);

	~Arrow();

	void Draw(Shader& meshShader, Camera& camera);

	void Move();

	glm::vec2 GetPosition();
	void FillVertices(float x, float y, float z);

private:
	float scale;
	glm::vec4 boundaries;

	float min_grad_vector;
	float arrow_step;
	int numberOfIterations;

	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;

	Mesh mesh; 

	float crntTime;
	float prevTime = 0.0f;
	float deltaTime = 0.0;

	glm::vec2 position;
	glm::vec2 Force;
	glm::vec2 Aciliration;
	glm::vec2 Velocity = glm::vec2(0, 0);

	float x;
	float y;
	float z;

	int iteration = 0;
};

#endif