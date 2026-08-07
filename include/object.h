#pragma once

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <memory>

class Mesh;
class MemLayout;
class Shader;

class Object {
private:
	std::shared_ptr<Mesh> mesh;
public:
	glm::mat4 model;
	std::shared_ptr<Shader> shader;

	glm::vec3 linearVelocity;
	float invMass; 
	
	void draw(void);
	
	void translate(glm::vec3 vector);
	void rotate(void);
	void scale(void);

	Object(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, glm::mat4 model, double invMass);
};

namespace memHelper {
	int getSize(GLenum type);
	int calcStrideSize(std::vector<MemLayout>& memLayout);
}