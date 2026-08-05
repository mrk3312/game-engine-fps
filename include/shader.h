#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertex_path, const char* fragment_path);
	void use(void);
	void set_float(const std::string& name, float value) const;
	void set_matrix_4f(const std::string& name, glm::mat4& matrix) const;
};

#endif

