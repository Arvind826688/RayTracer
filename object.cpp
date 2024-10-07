#include "object.h"

bool Sphere::intersect(const Ray& ray, float& t, Vec3& normal) const {
    Vec3 oc = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) return false;
    float sqrtDisc = sqrt(discriminant);
    float t0 = (-b - sqrtDisc) / (2.0f * a);
    float t1 = (-b + sqrtDisc) / (2.0f * a);

    t = (t0 < t1 && t0 > 0) ? t0 : t1;
    if (t < 0) return false;

    Vec3 hitPoint = ray.at(t);
    normal = (hitPoint - center).normalized();
    return true;
}

bool Plane::intersect(const Ray& ray, float& t, Vec3& normalOut) const {
    float denom = normal.dot(ray.direction);
    if (fabs(denom) < 1e-6) return false;
    
    t = (point - ray.origin).dot(normal) / denom;
    if (t < 0) return false;
    
    normalOut = normal;
    return true;
}
