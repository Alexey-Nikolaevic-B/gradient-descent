#include "Function.h"

float Function(float x, float z)
{
	float a = 0.08f;
	float b = 0.08f;
	float r = sqrt(a * x * x + b * z * z);
	return sin(x * x + 0.1 * z * z) / (0.1 + r * r) + (x * x + 1.9 * z * z) * exp(1 - r * r) / 4.0 + x*x/100 + z*z/100 - 1;
	//return (x-2.3)*(x-2.3)/25 + (z-2.5)*(z-2.5)/25 -0.14;
}


glm::vec2 DescentVector(float x, float z)
{
	float x_vector = Differentiate_X(x, z)/10;
	float z_vector = Differentiate_Z(x, z)/10;

	glm::vec2 descentVector = -glm::vec2(x_vector, z_vector);

	return descentVector;
}



//======================Differentiate=========================//
float Differentiate_X(float x, float z)
{
	float dx = 0.001; 

	return (Function(x + dx, z) - Function(x, z)) / dx;
}

float Differentiate_Z(float x, float z)
{
	float dz = 0.001; 

	return (Function(x, z + dz) - Function(x, z)) / dz;
}
//============================================================//



//=========================TRANSFORM_COORDINATES==========================//
float ToGraphScale_X(float variable/*, scale, resolution, boundaries*/)
{
	float SCALE = 15;
	glm::vec4 BOUNDARIES = glm::vec4(-12.0f, 12.0f, -12.0f, 12.0f); // (x1;x2 : y1;y2)
	return (variable) * (abs(BOUNDARIES[0]) + abs(BOUNDARIES[1])) / SCALE + BOUNDARIES[0];
}

float ToGraphScale_Z(float variable/*, scale, resolution, boundaries*/)
{
	float SCALE = 15;
	glm::vec4 BOUNDARIES = glm::vec4(-12.0f, 12.0f, -12.0f, 12.0f); // (x1;x2 : y1;y2)
	return (variable) * (abs(BOUNDARIES[2]) + abs(BOUNDARIES[3])) / SCALE + BOUNDARIES[2];
}

float ToGraphScale_Y(float variable/*, scale, resolution, boundaries*/)
{
	float SCALE = 15;
	glm::vec4 BOUNDARIES = glm::vec4(-12.0f, 12.0f, -12.0f, 12.0f); // (x1;x2 : y1;y2)
	return (variable) * (abs(BOUNDARIES[2]) + abs(BOUNDARIES[3])) / SCALE + BOUNDARIES[2];
}

float ToRealScale_X(float x/*, scale, resolution, boundaries*/)
{
	float SCALE = 15;
	glm::vec4 BOUNDARIES = glm::vec4(-12.0f, 12.0f, -12.0f, 12.0f); // (x1;x2 : y1;y2)
	return (x - BOUNDARIES[0]) * SCALE / (abs(BOUNDARIES[0]) + abs(BOUNDARIES[1]));
}

float ToRealScale_Z(float z/*, scale, resolution, boundaries*/)
{
	float SCALE = 15;
	glm::vec4 BOUNDARIES = glm::vec4(-12.0f, 12.0f, -12.0f, 12.0f); // (x1;x2 : y1;y2)
	return (z - BOUNDARIES[2]) * SCALE / (abs(BOUNDARIES[2]) + abs(BOUNDARIES[3]));
}

float ToRealScale_Y(float y/*, scale, resolution, boundaries*/)
{
	float SCALE = 15;
	glm::vec4 BOUNDARIES = glm::vec4(-12.0f, 12.0f, -12.0f, 12.0f); // (x1;x2 : y1;y2)
	return y * SCALE / (abs(BOUNDARIES[0]) + abs(BOUNDARIES[1]));
}
//========================================================================//