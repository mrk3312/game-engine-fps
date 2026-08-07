#include <memory>

#include "obj_builder.h"
#include "obj_init_data.h"
#include "object.h"
#include "shader.h"

glm::mat4 ObjBuilder::convObjPosToModel(const ObjData &objData){
    glm::mat4 model(1.0f);
    model = glm::translate(model, objData.pos);

    if (objData.rot.x + objData.rot.y + objData.rot.z != 0){
        model = glm::rotate(model, glm::radians(objData.deg), objData.rot);
    }
    
    model = glm::scale(model, {1.0f, 1.0f, 1.0f});

    return model;
}

std::unique_ptr<Object> ObjBuilder::requestObj(const char* meshLocation, const ObjData& objData ){
    this->loader.lastConstructedMesh = loader.loadModel(meshLocation);

    // currently one shader -> one object
    std::shared_ptr<Shader> shader = std::make_shared<Shader>("shader01.vs", "shader01.fs");
    
    std::cout << "this->loader.lastConstructedMesh " << this->loader.lastConstructedMesh << std::endl;
    glm::mat4 model = convObjPosToModel(objData);
    std::unique_ptr<Object> object = std::make_unique<Object>(this->loader.lastConstructedMesh, shader, model, objData.invMass);
    
    return object;
}
