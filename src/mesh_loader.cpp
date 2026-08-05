#include <vector>
#include <iostream>
#include <memory>

#include <glad.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stb_image.h>

#include "mesh.h"
#include "mesh_loader.h"

/* image class */

Image::Image(const char *location) {
	data = stbi_load(location, &width, &height, &nr_channels, 0);
	if (data) {
		std::cout << "successful" << std::endl;
	}
}

Image::~Image(void) {
	stbi_image_free(data);
}

int Image::uploadImageToGPU(void) {
	unsigned int ID;

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (this->data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// better error-handling
	this->release();

	return ID;
}

void Image::release(void) {
	stbi_image_free(data);
	data = nullptr;
	width = 0;
	height = 0;
	nr_channels = 0;
}

/* mesh loader class */
void MeshLoader::processNode(const aiNode *node, const aiScene *scene){

    for (int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(mesh);
    }
    
    for (int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }
}

unsigned int MeshLoader::loadTexture(const aiString *name){
    Image image(name->C_Str());
    unsigned int texture_id = image.uploadImageToGPU();
    return texture_id;
}

void MeshLoader::processMesh(const aiMesh *mesh, const aiScene *scene){
    for (int i = 0; i < mesh->mNumVertices; i++){
        struct Vertex vertex;
        
        vertex.pos.x = mesh->mVertices[i].x;
        vertex.pos.y = mesh->mVertices[i].y;
        vertex.pos.z = mesh->mVertices[i].z;
        vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
        vertex.texCoords.y = mesh->mTextureCoords[0][i].y;

        this->vertices.push_back(vertex);
    }

    for (int i = 0; i < mesh->mNumFaces; i++){
        for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++){
            unsigned int e = mesh->mFaces[i].mIndices[j];
            this->indices.push_back(e); 
        }
    }
    
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    aiString name;

    material->GetTexture(aiTextureType_DIFFUSE, 0, &name);
    std::cout << name.C_Str() << std::endl;

    auto value = this->loadedTextures.find(name.C_Str());
    unsigned int loadedTextureId = 0;

    if (value != loadedTextures.end()){
        loadedTextureId = value->second;
        std::cout << "Texture already created!" << std::endl;       
        
        return;
    }
    
    std::cout << "Creating new texture!" << std::endl;
    
    this->loadedTextures.insert({name.C_Str(), loadedTextureId});
    loadedTextureId = loadTexture(&name);
    this->textureId = loadedTextureId;
}

std::shared_ptr<Mesh> MeshLoader::loadModel(const char* loc){
    std::string key(loc);
    auto value = this->loadedMeshes.find(key);
    
    if (value != loadedMeshes.end()){
        std::cout << "Mesh is already loaded!" << std::endl;
        return value->second;
    }

    std::cout << "New mesh is requested!" << std::endl;

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(loc, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene){
        std::cerr << "Loader error: " << importer.GetErrorString() << "\n";
    }

    const aiNode *root = scene->mRootNode;
    
    processNode(root, scene);    
    
    for (int i = 0; i < this->meshes.size(); i++){
        processMesh(meshes[i], scene);
    }

    // hardcoded for now
    std::vector<MemLayout> memLayout = {
		{GL_FLOAT, 3},
		{GL_FLOAT, 2},
	};

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(this->vertices, this->indices, this->textureId, memLayout); 
    
    this->vertices.clear();
    this->indices.clear();
    this->meshes.clear();
    
    this->loadedMeshes.insert({key, mesh});

    std::cout << "Mesh: " << &(*mesh) << std::endl;
    return mesh;
}

MeshLoader::MeshLoader() : textureId(0){
    
}