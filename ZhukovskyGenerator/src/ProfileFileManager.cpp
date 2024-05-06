#include <iostream>
#include <fstream>
#include <cstdio>
#include "ProfileFileManager.h"

void ProfileFileManager::writeToFile(const std::filesystem::path pathToFile, Profile profile) {
    std::ofstream output(pathToFile);
    if (output.is_open()) {
        output << "x0 = " << profile.getX0()
            << ", y0 = " << profile.getY0()
            << ", t0 = " << profile.getRelativeThickness()
            << std::endl;

        Curve contour = profile.getContour();
        for (value_type i = 0; i < contour.size(); ++i) {
            output << contour[i].x << " ";
        }
        output << std::endl;

        for (value_type i = 0; i < contour.size(); ++i) {
            output << contour[i].y << " ";
        }
        output << std::endl;

        Curve middleLine = profile.getMiddleLine();
        for (value_type i = 0; i < middleLine.size(); ++i) {
            output << middleLine[i].x << " ";
        }
        output << std::endl;

        for (value_type i = 0; i < middleLine.size(); ++i) {
            output << middleLine[i].y << " ";
        }
        output << std::endl;

        Curve chord = profile.getChord();
        output << chord[0].x << " " << chord[1].x << std::endl;
        output << chord[0].y << " " << chord[1].y << std::endl;

        std::cout << "Profile was written in " << pathToFile << std::endl;
        output.close();
    }
    else {
        std::cerr << "Failed to write profile: file " << pathToFile << " not open" << std::endl;
    }
}

Profile ProfileFileManager::readFromFile(const std::filesystem::path pathToFile) {
}