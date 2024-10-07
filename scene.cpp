#include "scene.h"
#include "object.h"

Ray Scene::getRay(int x, int y, int width, int height) const {
    float aspectRatio = static_cast<float>(width) / height;
    float px = (2 * ((x + 0.5f) / width) - 1) * aspectRatio;
    float py = 1 - 2 * ((y + 0.5f) / height);
    Vec3 direction = Vec3(px, py, -1).normalize();
    return Ray(Vec3(0, 0, 0), direction);  // Camera positioned at origin
}

bool Scene::intersect(const Ray& ray, float& t, Vec3& normal, Material& material) const {
    bool hit = false;
    float closest = std::numeric_limits<float>::max();

    for (const auto& obj : objects) {
        float tTemp;
        Vec3 normalTemp;
        if (obj->intersect(ray, tTemp, normalTemp) && tTemp < closest) {
            hit = true;
            closest = tTemp;
            normal = normalTemp;
            material = obj->material;
        }
    }
    t = closest;
    return hit;
}
