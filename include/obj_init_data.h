#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ObjData{
    double invMass;
    glm::vec3 pos;
    glm::vec3 rot;
    float deg;
};