#pragma once
#include "ray.h"
#include "vector3.h"
#include "material.h"
#include <vector>

class Object;

class Scene {
public:
    std::vector<Object*> objects;

    Ray getRay(int x, int y, int width, int height) const;
    bool intersect(const Ray& ray, float& t, Vec3& normal, Material& material) const;

    void CreateSampleScene();  // To be implemented to set up sample objects in the scene
};
