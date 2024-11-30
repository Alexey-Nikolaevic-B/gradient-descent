#include "GradientDescent.h"

GradientDescent::~GradientDescent()
{
	for (int i = 0; i < arrows.size(); i++)
	{
		arrows[i].~Arrow();
	}
	heights.clear();
	heights.shrink_to_fit();
}

void GradientDescent::Initialize(float scale, glm::vec4 boundaries, int numberOfArrows, int numberOfIterations, float min_grad_vector, float arrow_step)
{
	GradientDescent::scale = scale;
	GradientDescent::boundaries = boundaries;
	GradientDescent::numberOfIterations = numberOfIterations;
	GradientDescent::min_grad_vector = min_grad_vector;
	GradientDescent::arrow_step = arrow_step;
}

void GradientDescent::GenerateArrows()
{
	arrows.push_back(Arrow(scale, boundaries, min_grad_vector, arrow_step, numberOfIterations));
}

void GradientDescent::Draw(Shader& meshShader, Camera& camera)
{
	for (int i = 0; i < arrows.size(); i++)
	{
		arrows[i].Draw(meshShader, camera);
	}
	UpdateArrows();
}

void GradientDescent::UpdateArrows()
{
	for (int i = 0; i < arrows.size(); i++)
	{
		arrows[i].Move();
	}
}

void GradientDescent::DeleteArrow()
{
	for (int i = 0; i < arrows.size(); i++)
	{
		arrows[i].~Arrow();
	}
	arrows.clear();
}

glm::vec2 GradientDescent::FindMinimum()
{
	heights.clear();

	float minimum = 1000;
	glm::vec2 minPosition = glm::vec2(0,0);
	glm::vec2 position = glm::vec2(0, 0);
	for (int i = 0; i < arrows.size(); i++)
	{
		position = arrows[i].GetPosition();
		if (Function(position[0], position[1]) < minimum)
		{
			minPosition = position;
			minimum = Function(minPosition[0], minPosition[1]);
		}
	}

	return minPosition;
}