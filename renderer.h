#pragma once
#include "scene.h"
#include <string>

class Renderer {
public:
    Scene& scene;

    Renderer(Scene& scene) : scene(scene) {}
    void Render(const std::string& filename);

private:
    Vec3 Trace(const Ray& ray, int depth) const;
};
