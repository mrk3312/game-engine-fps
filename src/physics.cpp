#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.h"
#include "physics.h"
#include <iostream>

void Physics::handleObjPhysics(Object &obj, float deltaTime){

/* 
*   calculate new velocity
*   F = m * g
*   J = F * dt
*   dv = m * g * dt * (1 / m)     
*
*/
    std::cout << "Object Inverse Mass " << obj.invMass << std::endl;
    
    glm::vec3 impulse = this->gravity * deltaTime;
    
    // new velocity
    obj.linearVelocity += impulse;

    std::cout << "Linear Velocity " << obj.linearVelocity.x << " " << obj.linearVelocity.y << " " << obj.linearVelocity.z << std::endl;
    
    // calculate step
    glm::vec3 step = obj.linearVelocity * deltaTime;
    std::cout << "Step " << step.x << " " << step.y << " " << step.z << std::endl << std::endl;

    // move
    obj.translate(step);
}

Physics::Physics(glm::vec3 gravity){
    this->gravity = gravity;
}