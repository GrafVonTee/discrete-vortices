#pragma once

#include <string>
#include <filesystem>
#include "Profile.h"

class ProfileFileManager {
    const char* format = "x0 = %.5f, y0 = %.5f, t = %.5f\n";

public:
    void writeToFile(const std::filesystem::path pathToFile, Profile profile);
    Profile readFromFile(const std::filesystem::path pathToFile);
};