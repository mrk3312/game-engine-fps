#include <memory>
#include <iostream>

#include "obj_builder.h"
#include "obj_init_data.h"
#include "object.h"

#include "scene.h"
#include "camera.h"

void Scene::addObj(const char* loc, const ObjData& objData){
    std::unique_ptr<Object> object = this->objBuilder.requestObj(loc, objData);
    this->objects.push_back(std::move(object)); 
}