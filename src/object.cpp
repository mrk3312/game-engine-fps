#include <glad.h>
#include <vector>
#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.h"
#include "mesh.h"

Object::Object(std::shared_ptr<Mesh> obj_mesh, std::shared_ptr<Shader> obj_shader, glm::mat4 obj_model, double obj_invMass)
	: mesh(obj_mesh), shader(obj_shader), model(obj_model), linearVelocity(glm::vec3{0.0f, 0.0f, 0.0f}), invMass(obj_invMass){
}

void Object::draw(void) {
	this->mesh->bind();
	glBindTexture(GL_TEXTURE_2D, this->mesh->textureId);
	glDrawElements(GL_TRIANGLES, this->mesh->indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Object::translate(glm::vec3 vector) {
	this->model = glm::translate(this->model, vector);
}