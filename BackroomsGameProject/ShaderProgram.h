#pragma once

#include <SDL3\SDL.h>
#include <GL\glew.h>
#include <glm.hpp>

#include <stdio.h>


class ShaderProgram
{
public:

	bool LoadFromSource(const char* vertexShader, const char* fragmentShader);

	void SetInt(const char* name, const int value) const;

	void SetVec3(const char* name, const glm::vec3& value) const;

	void SetMat4(const char* name, const glm::mat4& value) const;

	void Bind();

	void Unbind();

private:

	GLuint Create(const char* source, GLuint type);

	bool Link(GLuint vertexShader, GLuint fragmentShader);

	bool Validate(GLuint program, GLuint check);

	GLuint ShaderProgram;

};

