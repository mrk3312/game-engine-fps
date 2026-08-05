#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"

#include <iostream>

Camera::Camera(void) {

    this->firstClick = true;
    this->lastX = -400.0f;
    this->lastY = 300.0f;

	this->pitch = 0.0f;
	this->yaw = -89.0f;

    this->pos = glm::vec3(0.0f, 0.0f, 10.0f);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->orientation = glm::vec3{0.0f, 0.0f, -1.0f};

	this->projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    this->view = glm::lookAt(this->pos, this->pos + this->front, this->up);

}

void Camera::updateLookAt(void) {
    this->view = glm::lookAt(this->pos, this->pos + this->front, this->up);
}

void Camera::move(DirectionType dirType, float deltaTime) {
    float cameraSpeed = 2.5f * deltaTime;

    switch(dirType){
        case FORWARD:
            this->pos += glm::normalize(this->orientation) * cameraSpeed;
            break;
        case BACKWARD:
            this->pos -= glm::normalize(this->orientation) * cameraSpeed;    
            break;
        case LEFT:
            this->pos -= glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
            break;
        case RIGHT:
            this->pos += glm::normalize(glm::cross(this->front, this->up)) * cameraSpeed;
            break;
        default:
            break;
    }
}

void Camera::rotate(double newx, double newy) {
    if(this->firstClick){
		this->lastX = newx;
		this->lastY = newy;
		this->firstClick = false;
	}

	float xoffset = newx - this->lastX; 
	float yoffset = this->lastY - newy;
	
	this->lastX = newx;
	this->lastY = newy;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (this->pitch > 89.0f){
		this->pitch = 89.0f;
	}

	else if(this->pitch < -89.0f){
		this->pitch = -89.0f;
	}

    glm::vec3 direction;

    direction.x  = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	direction.y = sin(glm::radians(this->pitch));
	direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    
    this->front = glm::normalize(direction);

    this->orientation.x = this->front.x;
    this->orientation.z = this->front.z;
    
}

void Camera::helper(void){
        std::cout << "Front" << std::endl;
		
		for (int i = 0; i < 3; i++){
			std::cout << " " << this->front[i];
		}
		std::cout << std::endl;

		std::cout << "Up" << std::endl;
		for (int i = 0; i < 3; i++){
			std::cout << " " << this->up[i];
		}
		std::cout << std::endl;

		std::cout << "Pos" << std::endl;
		for (int i = 0; i < 3; i++){
			std::cout << " " << this->pos[i];
		}
		std::cout << std::endl;

        std::cout << "Orientation" << std::endl;
		for (int i = 0; i < 3; i++){
			std::cout << " " << this->orientation[i];
		}
		std::cout << std::endl;
}