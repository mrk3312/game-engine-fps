#pragma once

class Scene;
class Camera;

class Renderer{
private:
    Scene &scene;
    Camera &camera;
public:
    void render() const;
    Renderer(void) = delete;
    Renderer(Scene &scene, Camera &camera);
};
