#include <glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <filesystem>


#include "obj_init_data.h"

#include "scene.h"
#include "camera.h"
#include "action.h"
#include "physics.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	auto *self = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	self->rotate(xpos, ypos);
}

GLFWwindow* init_process(int width, int height, Camera& camera) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(width, height, "MyTriangle", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create a window!" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to init GLAD" << std::endl;
		return nullptr;
	}

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetWindowUserPointer(window, &camera);

	return window;
}

int main(void) {
	float lastFrame = 0.0f;
	Physics physics({0.0f, -10.0f, 0.0f});

	Camera camera;

	GLFWwindow *window = init_process(800, 600, camera);
	
	if (!window) {
		return -1;
	}

	Scene scene;

	scene.addObj("cube.obj", {0.0f, {0.0f, 0.0f, 0.0f}});
	scene.addObj("cube.obj", {0.01f, {10.0f, 5.0f, 0.0f}});
	scene.addObj("cube.obj", {0.1f, {0.0f, 5.0f, 0.0f}});

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime(); 
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;		
		process_input(window, camera, deltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// for (int i = 0; i < scene.objects.size(); i++){
		// 	std::cout << "Object " << i << " " << std::endl;
		// 	for (int j = 0; j < 4; j++){
		// 		for (int k = 0; k < 4; k++){
		// 			std::cout << scene.objects[i].model[j][k] << " ";
		// 		}
		// 		std::cout << std::endl;
		// 	}
		// }

		camera.updateLookAt();
		scene.update(physics, deltaTime);
		scene.render(camera);
		
		// camera.helper();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}



