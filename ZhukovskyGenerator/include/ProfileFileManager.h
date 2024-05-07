#pragma once

#include <string>
#include <filesystem>
#include "Profile.h"

class ProfileFileManager {
    const char* m_format = "x0 = %f, y0 = %f, t = %f\n";

public:
    void writeToFile(const std::filesystem::path pathToFile, Profile profile);
    Profile readFromFile(const std::filesystem::path pathToFile);
};