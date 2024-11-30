//---------------------------------------------------------
//	DESCRIPTION: Compiles vertex and fragment shaders
//---------------------------------------------------------

#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>


class Shader
{
public:
	~Shader();
	void Initialize(std::string vertexFile, std::string fragmentFile);
	std::string getFileContent(const char* filePath);
	void Use();

	GLuint& GetShaderProgram();

private:
	GLuint shaderProgram; 
};

#endif