#pragma once

#include <memory>
#include "mesh_loader.h"

class Object;
class ObjData;

class ObjBuilder{
private:
    MeshLoader loader;
    glm::mat4  convObjPosToModel(const ObjData &objData);
public:
    std::unique_ptr<Object> requestObj(const char* meshLocation, const ObjData &objData);
};