#include <iostream>
#include "mdv.h"
#include "ProfileGenerator.h"
#include "ProfileFileManager.h"

int main() {
    ProfileGenerator generator(-0.2, 0);
    Profile profile = generator.generateProfile();
    ProfileFileManager fmanager;
    fmanager.writeToFile(std::filesystem::current_path() / std::filesystem::path("zhukovsky-20.txt"), profile);
    profile = fmanager.readFromFile(std::filesystem::current_path() / std::filesystem::path("zhukovsky-20.txt"));
    return 0;
}