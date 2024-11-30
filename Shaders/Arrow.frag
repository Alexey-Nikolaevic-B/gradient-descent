#version 330 core

out vec4 FragColor;

in vec3 position;

void main()
{
	FragColor = vec4(0.0f + position.y, 1.0f, 0.0f + position.y, 1.0f);
};