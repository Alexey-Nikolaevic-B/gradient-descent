#include "Arrow.h"

Arrow::Arrow(float scale, glm::vec4 boundaries, float min_grad_vector, float arrow_step, int numberOfIterations)
{
	Arrow::scale = scale;
	Arrow::boundaries = boundaries;
	Arrow::min_grad_vector = min_grad_vector;
	Arrow::arrow_step = arrow_step;
	Arrow::numberOfIterations = numberOfIterations;

	position[0] = ((boundaries[0] + std::rand() % (int)(boundaries[1] * 2)) / 1, (boundaries[0] + std::rand() % (int)(boundaries[1] * 2)) / 1);
	position[1] = ((boundaries[2] + std::rand() % (int)(boundaries[3] * 2)) / 1, (boundaries[2] + std::rand() % (int)(boundaries[3] * 2)) / 1);

	indices =
	{
		0, 1, 2,
		3, 2, 1,

		4, 5, 6,
		7, 6, 5,

		0, 1, 4,
		4, 5, 1,
		5, 1, 2,
		5, 6, 2,
		2, 3, 6,
		6, 7, 3,
		3, 0, 7,
		4, 7, 0
	};

	mesh.Initialize(vertices, indices);
}

Arrow::~Arrow()
{
	mesh.~Mesh();
	vertices.clear();
	indices.clear();
	vertices.shrink_to_fit();
	indices.shrink_to_fit();
}


void Arrow::Draw(Shader& meshShader, Camera& camera)
{
	mesh.DrawTriangle(meshShader, camera, vertices);
}

void Arrow::Move()
{
	if ((iteration > numberOfIterations))
	{
		return;
	}

	float crntTime = glfwGetTime();
	if (crntTime - prevTime >= 1.0f / 2.0f)
	{
		deltaTime = crntTime - prevTime;
		prevTime = crntTime;
		if (deltaTime > 0.8f)
		{
			deltaTime = 0.8f;
		}
	}

	Aciliration = DescentVector(position[0], position[1]);
	if (glm::length(Aciliration) > 0.05f)
	{
		Aciliration = glm::normalize(Aciliration) * 0.05f;
	}

	Velocity += Aciliration;
	Velocity = Velocity - glm::normalize(Velocity) * glm::length(Velocity)/20.0f;
	position = position + Velocity * deltaTime + Aciliration * deltaTime * deltaTime / 2.0f;

	x = ToRealScale_X(position[0]);
	z = ToRealScale_Z(position[1]);
	y = ToRealScale_Y(Function(position[0], position[1]));

	FillVertices(x, y, z);

	iteration++;
}

void Arrow::FillVertices(float x, float y, float z)
{
	vertices =
	{
		glm::vec3(-0.1f + x, y,  0.1f + z), //Buttom Front left  0
		glm::vec3(0.1f + x , y,  0.1f + z),  //Buttom Front right 1
		glm::vec3(-0.1f + x,  y, -0.1f + z), //Buttom Back left   2
		glm::vec3(0.1f + x, y, -0.1f + z),  //Buttom Back right  3

		glm::vec3(-0.1f + x, 0.2 + y,  0.1f + z), //Up Front left  4
		glm::vec3(0.1f + x , 0.2 + y,  0.1f + z),  //Up Front right 5
		glm::vec3(-0.1f + x, 0.2 + y, -0.1f + z), //Up Back left   6
		glm::vec3(0.1f + x, 0.2 + y, -0.1f + z),  //Up Back right  7
	};
}

glm::vec2 Arrow::GetPosition()
{
	return position;
}
