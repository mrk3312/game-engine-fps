#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object;

class Physics{
private:
    glm::vec3 gravity;
public:
    void handleObjPhysics(Object &obj, float deltaTime);
    Physics() = delete;
    Physics(glm::vec3 gravity);
};