#include "utils.h"
#include <fstream>

void SaveImage(const std::string& filename, const std::vector<Vec3>& framebuffer, int width, int height) {
    std::ofstream file(filename, std::ios::binary);
    file << "P6\n" << width << " " << height << "\n255\n";

    for (const auto& color : framebuffer) {
        unsigned char r = static_cast<unsigned char>(std::min(1.0f, color.x) * 255);
        unsigned char g = static_cast<unsigned char>(std::min(1.0f, color.y) * 255);
        unsigned char b = static_cast<unsigned char>(std::min(1.0f, color.z) * 255);
        file << r << g << b;
    }
    file.close();
}
