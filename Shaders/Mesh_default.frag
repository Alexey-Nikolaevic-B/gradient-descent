#version 330 core

out vec4 FragColor;

in vec3 position;

void main()
{
	FragColor = vec4(0.9f + position.y/10, 0.0 + position.y/3, 0.0f, 1.0f);
};