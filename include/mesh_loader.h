#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "mesh.h"

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiString;

class Mesh;

class Image {
public:
	unsigned char* data;
	int width;
	int height;
	int nr_channels;
	
	Image(const Image&) = delete;

	Image(const char *location);
	~Image(void);

	Image& operator=(Image&&) = delete;
	int uploadImageToGPU(void);
	void release(void);
};

class MeshLoader{
private:
    std::unordered_map<std::string, std::shared_ptr<Mesh>> loadedMeshes;
    std::unordered_map<const char*, unsigned int> loadedTextures;    

    std::vector<aiMesh*> meshes;
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int textureId;

    void processNode(const aiNode *node, const aiScene *scene);
    void processMesh(const aiMesh *mesh, const aiScene *scene);
    unsigned int loadTexture(const aiString *name);

public:
    std::shared_ptr<Mesh> lastConstructedMesh;
    std::shared_ptr<Mesh> loadModel(const char* loc);
    MeshLoader();
};