#include "Shader.h"

Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}

void Shader::Initialize(std::string vertexFile, std::string fragmentFile)
{
	std::string vertexCode = getFileContent(vertexFile.c_str());
	std::string fragmentCode = getFileContent(fragmentFile.c_str());

	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


std::string Shader::getFileContent(const char* filePath)
{
	std::string content;
	std::string line;

	std::ifstream fin;
	fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try
	{
		fin.open(filePath);
		while (!fin.eof())
		{
			std::getline(fin, line);
			content += line + "\n";
		}
	}
	catch (const std::ifstream::failure& exception)
	{
		std::cout << exception.what() << std::endl;
		std::cout << exception.code() << std::endl;
		std::cout << "Unable to open the file: " << filePath << std::endl;
	}
	fin.close();
	return content;
}

void Shader::Use()
{
	glUseProgram(shaderProgram);
}

GLuint& Shader::GetShaderProgram()
{
	return shaderProgram;
}