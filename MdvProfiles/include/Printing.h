#pragma once

#include <string>
#include "Profile.h"
#include "Platform.h"
#include "Statistic.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

void printCurve(const Curve& curve);
void printProfile(Profile& profile);
void printPlatforms(const std::vector<Platform>& platforms, const std::string additionalInfo);
void printPolar(const StatisticManager &manager, const std::string additionalInfo);