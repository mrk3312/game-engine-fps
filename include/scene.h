#pragma once

#include <vector>
#include <memory>

#include "obj_builder.h"
#include "object.h"

class Camera;
class Physics;

class Scene{
private:
    ObjBuilder objBuilder;
public:    
    std::vector<std::unique_ptr<Object>> objects;

    void update(Physics& physics, float deltaTime);
    void render(Camera &camera);
    void addObj(const char *loc, const ObjData& objData);
    void removeObj();
    Scene(void) {};
};