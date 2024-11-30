#include "Graph.h"

void Graph::Initialize(GLFWwindow* window, float scale, float resolution, glm::vec4 boundaries)
{
	Graph::window = window;

	Graph::scale = scale;
	Graph::resolution = resolution;
	Graph::boundaries = boundaries;

	plane.Initialize(GenerateVertices(), GenerateLineIndices());
	net.Initialize(GenerateNetVertices(), GenerateNetIndices());
}

void Graph::Draw(Shader& meshShader, Shader& netShader, Camera& camera)
{
	plane.DrawLine(meshShader, camera);
	net.DrawLine(netShader, camera);
}

//==================================================================//
std::vector<glm::vec3>& Graph::GenerateVertices()
{
	const float step = (scale / resolution);
	float y;
	float x;
	float z;

	for (float real_z = 0; real_z <= scale + 1/ resolution; real_z += step)
	{
		for (float real_x = 0; real_x <= scale + 1 / resolution; real_x += step)
		{
			x = ToGraphScale_X(real_x);
			z = ToGraphScale_Z(real_z);
			y = Function(x, z);
			y = y * scale / (abs(boundaries[0]) + abs(boundaries[1]));
			planeVertices.push_back(glm::vec3(real_x, y, real_z));
		}
	}

	return planeVertices;
}

std::vector<GLuint>& Graph::GeneratePointIndices()
{
	const float step = resolution;
	for (int i = 0; i <= resolution * resolution; i++)
	{
		planeIndices.push_back(i);
	}
	return planeIndices;
}

std::vector<GLuint>& Graph::GenerateLineIndices()
{
	const float step = resolution;

	for (int z = 0; z < (step + 1) * step; z+= (step + 1))
	{
		for (int x = 0; x < resolution; x++)
		{
			if (z == 0)
			{
				planeIndices.push_back(x + z);
				planeIndices.push_back(x + z + 1);
			}

			if (x == 0)
			{
				planeIndices.push_back(x + z);
				planeIndices.push_back(x + z + step + 1);
			}

			planeIndices.push_back(x + z + 1);
			planeIndices.push_back(x + z + step + 1);

			planeIndices.push_back(x + z + 1);
			planeIndices.push_back(x + z + step + 2);

			planeIndices.push_back(x + z + step + 1);
			planeIndices.push_back(x + z + step + 2);
		}
	}
	return planeIndices;
}

std::vector<glm::vec3>& Graph::GenerateNetVertices()
{
	const float step = scale / (abs(boundaries[0]) + abs(boundaries[1]));

	const float min_x = 0;
	const float min_y = -scale / 8;
	const float min_z = 0;

	const float max_x = scale;
	const float max_y = scale / 1.5;
	const float max_z = scale;

	for (float x = min_x; x <= max_x + 1 / resolution; x += step)
	{
		netVertices.push_back(glm::vec3(x, max_y, min_z));
		netVertices.push_back(glm::vec3(x, min_y, min_z));
		netVertices.push_back(glm::vec3(x, min_y, max_z));
	}
	for (float z = min_z; z <= max_z + 1 / resolution; z += step)
	{
		netVertices.push_back(glm::vec3(min_x, max_y, z));
		netVertices.push_back(glm::vec3(min_x, min_y, z));
		netVertices.push_back(glm::vec3(max_x, min_y, z));
	}
	for (float y = min_y; y <= max_y + 1 / resolution; y += step)
	{
		netVertices.push_back(glm::vec3(max_x, y, min_z));
		netVertices.push_back(glm::vec3(min_x, y, min_z));
		netVertices.push_back(glm::vec3(min_x, y, max_z));
	}
	return netVertices;
}
std::vector<GLuint>& Graph::GenerateNetIndices()
{
	for (int i = 0; i < scale * (abs(boundaries[0]) + abs(boundaries[1])); i += 3)
	{
		netIndices.push_back(i);
		netIndices.push_back(i + 1);
		netIndices.push_back(i + 1);
		netIndices.push_back(i + 2);
	}
	return netIndices;
}
//==================================================================//