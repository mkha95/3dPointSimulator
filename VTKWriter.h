#pragma once
#include "Point.h"
#include <vector>
#include <string>

class VTKWriter {
public:
    static void writePoints(const std::vector<Point>& points, const std::string& filename, int timeStep);
    static void writeTimeSeriesPoints(const std::vector<std::vector<Point>>& pointsHistory, const std::string& baseFilename);
};