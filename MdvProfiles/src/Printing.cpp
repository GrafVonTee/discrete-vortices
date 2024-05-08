#include "Printing.h"
#include <Eigen/Dense>

void printCurve(const Curve& curve) {
    std::vector<value_type> x(curve.size()), y(curve.size());
    for (int i = 0; i < curve.size(); ++i) {
        const Point& point = curve[i];
        x.push_back(point.x);
        y.push_back(point.y);
    }
    plt::plot(x, y);
}

void printProfile(Profile& profile) {
    plt::figure_size(1280, 720);
    
    printCurve(profile.getContour());
    // printCurve(profile.getChord());
    // printCurve(profile.getMiddleLine());

    plt::ylim(-1, 1);

    plt::title(
        "x0 = " + std::to_string(profile.getX0())
        + ", y0 = " + std::to_string(profile.getY0())
        + ", t0 = " + std::to_string(profile.getRelativeThickness())
        + ", seg = " + std::to_string(profile.getNumberOfSegments()));

    plt::save("./zhukovsky"
        + std::to_string(profile.getX0())
        + std::to_string(profile.getY0())
        + ".png");
}

void printPlatforms(const std::vector<Platform>& platforms, const std::string additionalInfo) {
    plt::figure_size(1280, 720);

    for (const auto& platform: platforms) {
        Point begin(platform.getLine()[0]), end(platform.getLine()[1]), center(platform.getMiddlePoint());
        std::vector<value_type> x {begin.x, end.x}, y {begin.y, end.y};
        plt::plot(x, y, "b");

        double sizeOfNormals = 0.1;
        Eigen::Vector2d normal = platform.getNormalVector() * sizeOfNormals;
        
        std::vector<value_type> nX {center.x, center.x + normal(0)}, nY {center.y, center.y + normal(1)};
        plt::plot(nX, nY, "r--");
    }

    plt::xlim(-1, 5);
    plt::ylim(-1, 1);

    plt::title("seg = " + std::to_string(platforms.size()));

    plt::save("./segmentation"+additionalInfo+".png");
}