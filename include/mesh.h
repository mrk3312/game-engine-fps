#pragma once

#include <vector>
#include <iostream>

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef unsigned int GLenum;

class MemLayout {
public:
	GLenum type;
	unsigned int len;
};

struct Vertex {
public:
	glm::vec3 pos;
	glm::vec2 texCoords;
};

class Mesh {
private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	void sendDataToGPU(std::vector<MemLayout>& memLayout) const;
	template <typename T>
	void initBuffer(unsigned int* handle, GLenum target, std::vector<T>& vect);
	
public:
	int verticesSize;
	int indicesSize;

	unsigned int textureId;
	
	inline void bind(void) const { glBindVertexArray(this->VAO);};
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, unsigned int textureId, std::vector<MemLayout>& memLayout);
};

namespace memHelper {
	int getSize(GLenum type);
	int calcStrideSize(std::vector<MemLayout>& memLayout);
}