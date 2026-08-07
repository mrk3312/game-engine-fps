#include <memory>
#include <iostream>

#include "obj_builder.h"
#include "obj_init_data.h"
#include "object.h"

#include "scene.h"
#include "camera.h"
#include "shader.h"
#include "physics.h"

void Scene::addObj(const char* loc, const ObjData& objData){
    std::unique_ptr<Object> object = this->objBuilder.requestObj(loc, objData);
    this->objects.push_back(std::move(object)); 
}

void Scene::update(Physics& physicsData, float deltaTime){
    
    for (int i = 0; i < this->objects.size(); i++){
        Object& object = *(this->objects[i]);

        if (object.invMass == 0.0f){
            continue;
        } 
        physicsData.handleObjPhysics(object, deltaTime);
    }

}

void Scene::render(Camera &camera) {
    for (int i = 0; i < this->objects.size(); i++){
        Object& object = *(this->objects[i]);
        
        object.shader->use();
		object.shader->set_matrix_4f("model", object.model);
		object.shader->set_matrix_4f("view", camera.view);
		object.shader->set_matrix_4f("projection", camera.projection);
		
		object.draw();
    }
}