#include <glad.h>
#include <vector>
#include <iostream>
#include <memory>

#include "object.h"
#include "mesh.h"

Object::Object(std::shared_ptr<Mesh> obj_mesh, std::shared_ptr<Shader> obj_shader, glm::mat4 obj_model)
	: mesh(obj_mesh), shader(obj_shader), model(obj_model){
}

void Object::draw(void) {
	this->mesh->bind();
	glBindTexture(GL_TEXTURE_2D, this->mesh->textureId);
	glDrawElements(GL_TRIANGLES, this->mesh->indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}