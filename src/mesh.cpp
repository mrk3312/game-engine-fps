#include <glad.h>
#include "mesh.h"

/* memhelper namespace */

int memHelper::getSize(GLenum type) {
	switch (type) {
		case GL_FLOAT: {
			return sizeof(float);
		}
		case GL_INT: {
			return sizeof(int);
		}
		case GL_BOOL: {
			return sizeof(bool);
		}
		default: {
			return -1;
		}
	}
}

int memHelper::calcStrideSize(std::vector<MemLayout>& memLayout) {
	int strideSize = 0;
	
	for (int i = 0; i < memLayout.size(); i++) {
		strideSize += memLayout[i].len * memHelper::getSize(memLayout[i].type);
	}
	return strideSize;
}

void Mesh::sendDataToGPU(std::vector<MemLayout>& memLayout) const {
	int offset = 0;
	int strideSize = memHelper::calcStrideSize(memLayout);

	for (int i = 0; i < memLayout.size(); i++) {
		int typeSize = memHelper::getSize(memLayout[i].type);
		glVertexAttribPointer(i, memLayout[i].len, memLayout[i].type, GL_FALSE, strideSize, (void*)(offset));
		glEnableVertexAttribArray(i);
		offset += memLayout[i].len * typeSize;
	}
}

template <typename T>
void Mesh::initBuffer(unsigned int* handle, GLenum target, std::vector<T> &vect) {
	glGenBuffers(1, handle);
	glBindBuffer(target, *handle);
	glBufferData(target, vect.size() * sizeof(T), vect.data(), GL_STATIC_DRAW);
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, unsigned int textureId, std::vector<MemLayout>& memLayout) {

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	this->initBuffer(&this->VBO, GL_ARRAY_BUFFER, vertices);
	
	this->sendDataToGPU(memLayout);
	this->verticesSize = vertices.size();
	this->indicesSize = indices.size();
	this->initBuffer(&this->EBO, GL_ELEMENT_ARRAY_BUFFER, indices);

	this->textureId = textureId;
}