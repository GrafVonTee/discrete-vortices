#include <iostream>
#include <Eigen/Dense>
#include "Mdv.h"
#include "ProfileGenerator.h"
#include "ProfileFileManager.h"
#include "Printing.h"

enum class ProfileFileManagerOption {
    ReadProfile,
    WriteProfile
};

ProfileFileManagerOption greetings() {
    std::cout << "Greetings, Traveler!" << std::endl;
    std::cout << "Choose an option to proceed (0 -- read, 1 -- write new): ";
    char option;
    do {
        std::cin >> option;
    } while (std::cin.fail());

    return (option == '0')
        ? ProfileFileManagerOption::ReadProfile
        : ProfileFileManagerOption::WriteProfile;
}

Profile readProfile() {
    std::string fileOutput;
    std::cout << "Enter file input name: ";
    std::cin >> fileOutput;

    ProfileFileManager fmanager;
    return fmanager.readFromFile(std::filesystem::current_path() / std::filesystem::path(fileOutput));
}

Profile writeProfile() {
    value_type x0, y0;
    std::cout << "Enter x0 and y0: ";
    std::cin >> x0 >> y0;

    std::string fileOutput;
    std::cout << "Enter file output name: ";
    std::cin >> fileOutput;

    ProfileGenerator generator(x0, y0);
    Profile profile = generator.generateProfile();
    ProfileFileManager fmanager;
    fmanager.writeToFile(std::filesystem::current_path() / std::filesystem::path(fileOutput), profile);

    return profile;
}

int main() {
    Profile profile = Profile(0, 0, 0);

    ProfileFileManagerOption option = greetings();
    switch (option) {
        case ProfileFileManagerOption::ReadProfile:
            profile = readProfile();
            break;
        case ProfileFileManagerOption::WriteProfile:
            profile = writeProfile();
            break;
        default:
            break;
    }

    printProfile(profile);

    int numberOfSegments;
    std::cout << "Enter number of segments: ";
    std::cin >> numberOfSegments;

    std::vector<Platform> platformCurve = splitCurve(profile.getMiddleLine(), numberOfSegments);
    moveCurve(platformCurve, profile.getChord()[0]);

    printPlatforms(platformCurve, "-default");

    double minAngle(-30.0 / 180.0 * M_PI), maxAngle(30.0 / 180.0 * M_PI);
    double angleShift(M_PI / 180.0);

    const Environment env = { 1000.0, 50.0 };
    StatisticManager manager = getFullAirflow(
        platformCurve,
        env,
        angleShift,
        minAngle,
        maxAngle,
        profile.getChordLength()
    );

    std::cout << "Zero Lift angle = " << manager.getZeroLiftAngle() / (2*M_PI) * 360 << std::endl;
    std::cout << "Critical angle = " << manager.getCriticalAngle() / (2*M_PI) * 360 << std::endl;
    std::cout << "Derivative C_y = " << manager.getDerivativeCy() << std::endl;
    std::cout << "Derivative m_Z = " << manager.getDerivativeMz() << std::endl;

    return 0;
}