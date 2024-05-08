#pragma once

#include "Profile.h"
#include "Platform.h"
#include <string>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

void printCurve(const Curve& curve);
void printProfile(Profile& profile);
void printPlatforms(const std::vector<Platform>& platforms, const std::string additionalInfo);