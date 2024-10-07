#pragma once
#include "vector3.h"

class Material {
public:
    Vec3 color;
    float reflectivity;
    float refractiveIndex;

    Material(const Vec3& color, float reflectivity, float refractiveIndex)
        : color(color), reflectivity(reflectivity), refractiveIndex(refractiveIndex) {}

    Vec3 reflect(const Vec3& incident, const Vec3& normal) const;
    bool refract(const Vec3& incident, const Vec3& normal, float eta, Vec3& refracted) const;
    float fresnel(const Vec3& incident, const Vec3& normal, float& reflectance) const;
};
