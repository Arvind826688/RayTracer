#include "renderer.h"
#include "utils.h"
#include <thread>
#include <vector>

Vec3 Renderer::Trace(const Ray& ray, int depth) const {
    if (depth > 5) return Vec3(0, 0, 0);  // Base case for recursion

    float t;
    Vec3 normal;
    Material material;

    if (scene.intersect(ray, t, normal, material)) {
        Vec3 hitPoint = ray.origin + ray.direction * t;
        Vec3 reflectionDir = ray.direction - normal * 2 * ray.direction.dot(normal);
        Ray reflectedRay(hitPoint, reflectionDir);

        Vec3 reflectedColor = Trace(reflectedRay, depth + 1);
        return material.color * (0.8f * reflectedColor);  // Reflected color
    }
    return Vec3(0.5, 0.7, 1.0);  // Background color
}

void Renderer::Render(const std::string& filename) {
    const int numThreads = std::thread::hardware_concurrency();
    const int width = 800, height = 600;

    std::vector<std::thread> threads;
    std::vector<Vec3> framebuffer(width * height);

    auto renderRow = [&](int yStart, int yEnd) {
        for (int y = yStart; y < yEnd; ++y) {
            for (int x = 0; x < width; ++x) {
                Ray ray = scene.getRay(x, y, width, height);
                Vec3 color = Trace(ray, 0);
                framebuffer[y * width + x] = color;
            }
        }
    };

    int rowsPerThread = height / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int yStart = i * rowsPerThread;
        int yEnd = (i == numThreads - 1) ? height : yStart + rowsPerThread;
        threads.emplace_back(renderRow, yStart, yEnd);
    }

    for (auto& thread : threads) thread.join();

    SaveImage(filename, framebuffer, width, height);
}
