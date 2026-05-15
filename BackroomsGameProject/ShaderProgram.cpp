#include "ShaderProgram.h"

bool ShaderProgram::LoadFromSource(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
	auto vertexShader = Create(vertexShaderSrc, GL_VERTEX_SHADER);
	auto fragmentShader = Create(fragmentShaderSrc, GL_FRAGMENT_SHADER);

	return Link(vertexShader, fragmentShader);
}

void ShaderProgram::SetInt(const char* name, const int value) const
{
	auto location = glGetUniformLocation(ShaderProgram, name);
	glUniform1i(location, value);
}

void ShaderProgram::SetVec3(const char* name, const glm::vec3& value) const
{
	auto location = glGetUniformLocation(ShaderProgram, name);
	glUniform3fv(location, 1, &value[0]);
}

void ShaderProgram::SetMat4(const char* name, const glm::mat4& value) const
{
	auto location = glGetUniformLocation(ShaderProgram, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::Bind()
{
	glUseProgram(ShaderProgram);
}

GLuint ShaderProgram::Create(const char* source, GLuint type)
{
	GLuint shaderProgram = glCreateShader(type);

	glShaderSource(shaderProgram, 1, &source, NULL);
	glCompileShader(shaderProgram);

	if (Validate(shaderProgram, GL_COMPILE_STATUS))
	{
		return shaderProgram;
	}

	return 0;
}

bool ShaderProgram::Link(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	if (Validate(program, GL_LINK_STATUS))
	{
		ShaderProgram = program;
		return true;
	}

	return false;
}

bool ShaderProgram::Validate(GLuint program, GLuint check)
{
	
	GLint success;
	glGetShaderiv(program, check, &success);

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		printf("Unable to compile vertex shader %s\n", infoLog);
		return false;
	}




	return true;
}
