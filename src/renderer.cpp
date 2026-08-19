#include "renderer.h"
#include "shader.h"
#include "scene.h"
#include "camera.h"

void Renderer::render(void) const{
    
    for (int i = 0; i < this->scene.objects.size() ; i++){
        Object& object = *(this->scene.objects[i]);
        
        object.shader->use();
		object.shader->set_matrix_4f("model", object.model);
		object.shader->set_matrix_4f("view", this->camera.view);
		object.shader->set_matrix_4f("projection", this->camera.projection);
		
		object.draw();
    }

}

Renderer::Renderer(Scene &obj_scene, Camera &obj_camera) : scene(obj_scene), camera(obj_camera){

}