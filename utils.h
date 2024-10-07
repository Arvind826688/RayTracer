#pragma once
#include <vector>
#include <string>
#include "vector3.h"

void SaveImage(const std::string& filename, const std::vector<Vec3>& framebuffer, int width, int height);
