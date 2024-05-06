#include <iostream>
#include "mdv.h"
#include "ProfileGenerator.h"
#include "ProfileFileManager.h"

enum class ProfileFileManagerOption {
    ReadProfile,
    WriteProfile
};

ProfileFileManagerOption greetings() {
    std::cout << "Greeting, Traveler!" << std::endl;
    std::cout << "Choose an option to proceed (0 -- read, 1 -- write)";
}

Profile readProfile() {

}

void writeProfile() {

}

int main() {
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
    return 0;
}