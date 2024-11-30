#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <algorithm> // std::min_element
#include <iterator>  // std::begin, std::end
#include "Arrow.h"

class GradientDescent
{
public:
	~GradientDescent();

	void Initialize(float scale, glm::vec4 boundaries, int numberOfArrows, int numberOfIterations, float min_grad_vector, float arrow_step);

	void GenerateArrows();
	void Draw(Shader& meshShader, Camera& camera);
	void UpdateArrows();

	void DeleteArrow();

	glm::vec2 FindMinimum();

private:
	float scale;
	glm::vec4 boundaries;

	int numberOfIterations;

	float min_grad_vector;
	float arrow_step;

	std::vector<Arrow> arrows;

	std::vector<float> heights;
};

#endif