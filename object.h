#pragma once
#include "vector3.h"
#include "ray.h"
#include "material.h"

class Object {
public:
    Material* material;
    Object(Material* material) : material(material) {}
    virtual bool intersect(const Ray& ray, float& t, Vec3& normal) const = 0;
};

class Sphere : public Object {
public:
    Vec3 center;
    float radius;

    Sphere(const Vec3& center, float radius, Material* material)
        : Object(material), center(center), radius(radius) {}

    bool intersect(const Ray& ray, float& t, Vec3& normal) const override;
};

class Plane : public Object {
public:
    Vec3 point, normal;

    Plane(const Vec3& point, const Vec3& normal, Material* material)
        : Object(material), point(point), normal(normal.normalized()) {}

    bool intersect(const Ray& ray, float& t, Vec3& normal) const override;
};
