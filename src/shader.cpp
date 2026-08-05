#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "shader.h"

Shader::Shader(const char* vertex_path, const char* fragment_path) {
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	std::string vertexCode;
	std::string fragmentCode;

	vertexFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	fragmentFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try {
		vertexFile.open(vertex_path);
		fragmentFile.open(fragment_path);
		
		std::stringstream vertexStream;
		std::stringstream fragmentStream;

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::fstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	
	int vShader, fShader;
	int success;
	char infoLog[512];

	vShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vShader, 1, &vShaderCode, nullptr);
	glCompileShader(vShader);

	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vShader, 512, nullptr, infoLog);

		std::cout << infoLog << std::endl;
	}

	fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fShader, 1, &fShaderCode, nullptr);
	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);


	if (!success) {
		glGetShaderInfoLog(fShader, 512, nullptr, infoLog);

		std::cout << infoLog << std::endl;
	}

	ID = glCreateProgram();

	glAttachShader(ID, vShader);
	glAttachShader(ID, fShader);

	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(ID, 512, nullptr, infoLog);
		std::cout << infoLog << std::endl;
	}
	
	std::cout << "Shader loaded successfully!" << std::endl;
}

void Shader::use(void) {
	glUseProgram(this->ID);
}

void Shader::set_float(const std::string& name, float value) const {
	int loc = glGetUniformLocation(this->ID, name.c_str());
	glUniform1f(loc, value);
}

void Shader::set_matrix_4f(const std::string& name, glm::mat4& matrix) const {
	int loc = glGetUniformLocation(this->ID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
}