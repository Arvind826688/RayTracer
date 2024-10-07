#include "material.h"
#include <cmath>

Vec3 Material::reflect(const Vec3& incident, const Vec3& normal) const {
    return incident - normal * 2.0f * incident.dot(normal);
}

bool Material::refract(const Vec3& incident, const Vec3& normal, float eta, Vec3& refracted) const {
    float cosi = -std::max(-1.0f, std::min(1.0f, incident.dot(normal)));
    Vec3 n = normal;
    if (cosi < 0) { cosi = -cosi; n = -normal; eta = 1.0f / eta; }
    float k = 1 - eta * eta * (1 - cosi * cosi);
    if (k < 0) return false;
    refracted = incident * eta + n * (eta * cosi - sqrtf(k));
    return true;
}

float Material::fresnel(const Vec3& incident, const Vec3& normal, float& reflectance) const {
    float cosi = std::clamp(incident.dot(normal), -1.0f, 1.0f);
    float etai = 1, etat = refractiveIndex;
    if (cosi > 0) std::swap(etai, etat);

    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    if (sint >= 1) {
        reflectance = 1.0f;
        return reflectance;
    }

    float cost = sqrtf(std::max(0.f, 1 - sint * sint));
    cosi = fabsf(cosi);
    float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
    float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
    reflectance = (Rs * Rs + Rp * Rp) / 2;
    return reflectance;
}
