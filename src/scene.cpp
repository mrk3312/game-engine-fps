#include <memory>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh_loader.h"
#include "object.h"
#include "scene.h"
#include "camera.h"
#include "shader.h"

glm::mat4 Scene::convObjPosToModel(const objPos &objPos){
    glm::mat4 model(1.0f);
    model = glm::translate(model, objPos.pos);

    if (objPos.rot.x + objPos.rot.y + objPos.rot.z != 0){
        model = glm::rotate(model, glm::radians(objPos.deg), objPos.rot);
    }
    
    model = glm::scale(model, {1.0f, 1.0f, 1.0f});

    return model;
}

void Scene::addObj(const char* loc, const objPos& objPos){
    this->loader.lastConstructedMesh = loader.loadModel(loc);

    // currently one shader -> one object
    std::shared_ptr<Shader> shader = std::make_shared<Shader>("shader01.vs", "shader01.fs");
    
    std::cout << "this->loader.lastConstructedMesh " << this->loader.lastConstructedMesh << std::endl;
    glm::mat4 model = convObjPosToModel(objPos);
    Object object(this->loader.lastConstructedMesh, shader, model);
    this->objects.push_back(object);
}

void Scene::render(Camera &camera) {
    for (int i = 0; i < this->objects.size(); i++){
        Object *object = &this->objects[i]; 

        object->shader->use();
		object->shader->set_matrix_4f("model", object->model);
		object->shader->set_matrix_4f("view", camera.view);
		object->shader->set_matrix_4f("projection", camera.projection);
		
		object->draw();
    }
}