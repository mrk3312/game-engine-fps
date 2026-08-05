#pragma once

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <memory>

#include "shader.h"

class Mesh;
class MemLayout;

class Object {
private:
	std::shared_ptr<Mesh> mesh;

public:
	glm::mat4 model;
	std::shared_ptr<Shader> shader;
	void draw(void);
	
	void translate();
	void rotate();
	void scale();

	Object(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, glm::mat4 model);
};

namespace memHelper {
	int getSize(GLenum type);
	int calcStrideSize(std::vector<MemLayout>& memLayout);
}