#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum DirectionType{
    NONE = 0,
    LEFT,
    RIGHT,
    FORWARD,
    BACKWARD
};

class Camera{
private:
    double lastX;
	double lastY;
	bool firstClick;

    float pitch;
    float yaw;

    glm::vec3 orientation;
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    
public:

    glm::mat4 view;
    glm::mat4 projection;

    Camera(void);
    void rotate(double newX, double newY);
    void move(DirectionType dirType, float deltaTime);
    void updateLookAt();
    
    void helper(void);
};