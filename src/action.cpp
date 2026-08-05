#include <GLFW/glfw3.h>
#include <vector>

#include "camera.h"
#include "action.h"

void process_input(GLFWwindow* window, Camera& camera, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.move(DirectionType::FORWARD, deltaTime);    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.move(DirectionType::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.move(DirectionType::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.move(DirectionType::RIGHT, deltaTime);
}