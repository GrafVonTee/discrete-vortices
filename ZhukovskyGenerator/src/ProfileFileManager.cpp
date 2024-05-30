#include <iostream>
#include <fstream>
#include <cstdio>
#include "ProfileFileManager.h"
#include "ProfileGenerator.h"

void ProfileFileManager::writeToFile(const std::filesystem::path pathToFile, Profile &profile) {
    std::ofstream output(pathToFile);
    if (output.is_open()) {
        output << "x0 = " << profile.getX0()
            << ", y0 = " << profile.getY0()
            << ", t0 = " << profile.getRelativeThickness()
            << ", seg = " << profile.getNumberOfSegments()
            << std::endl;

        Curve contour = profile.getContour();
        for (int i = 0; i < contour.size(); ++i) {
            output << contour[i].x << " ";
        }
        output << std::endl;

        for (int i = 0; i < contour.size(); ++i) {
            output << contour[i].y << " ";
        }
        output << std::endl;

        Curve middleLine = profile.getMiddleLine();
        for (int i = 0; i < middleLine.size(); ++i) {
            output << middleLine[i].x << " ";
        }
        output << std::endl;

        for (int i = 0; i < middleLine.size(); ++i) {
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
        std::cerr << "Failed to write profile: file " << pathToFile << std::endl;
    }
}

Profile ProfileFileManager::readFromFile(const std::filesystem::path pathToFile) {
    std::ifstream input(pathToFile);
    if (input.is_open()) {
        std::string inpStr;
        value_type x0(-1000), y0(-1000), t0(-1000);
        segment_number_type seg(-1000);
        while (seg == -1000) {
            input >> inpStr;
            if (inpStr == "=") {
                if (x0 == -1000) {
                    input >> x0;
                }
                else if (y0 == -1000) {
                    input >> y0;
                }
                else if (t0 == -1000) {
                    input >> t0;
                }
                else {
                    input >> seg;
                }
            }
        }
        std::cout << "Profile successfully loaded\n";
        return ProfileGenerator(x0, y0).generateProfile(seg);
    }
    else {
        std::cerr << "Failed to open profile: file " << pathToFile << std::endl;
        return ProfileGenerator(0, 0).generateProfile();
    }
}