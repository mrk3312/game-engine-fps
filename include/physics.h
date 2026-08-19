#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene;
class Object;

class Physics{
private:
    Scene &scene;
    glm::vec3 gravity;
    void handleObjPhysics(Object &obj, float deltaTime);
public:
    void simulateScene(float deltaTime);
    Physics() = delete;
    Physics(glm::vec3 gravity, Scene &scene);
};