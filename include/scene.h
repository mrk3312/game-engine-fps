#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.h"
#include "mesh_loader.h"

class Camera;

struct objPos{
    glm::vec3 pos;
    glm::vec3 rot;
    float deg;
};

class Scene{
private:
    glm::mat4 convObjPosToModel(const objPos &objPos);
public:    
    MeshLoader loader;
    std::vector<Object> objects;

// public:
    void render(Camera &camera);
    void addObj(const char *loc, const objPos& objPos);
    void removeObj();
    Scene(void) {};
};