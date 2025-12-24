#include "TrajectoryLogger.h"

TrajectoryLogger::TrajectoryLogger(const std::string& filename) : filename(filename) {}

void TrajectoryLogger::addPoint(double x, double y, double z, double speed, double time) {
    points.push_back({ x, y, z, speed, time });
}

bool TrajectoryLogger::saveToCSV() {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    file << "time,x,y,z,speed\n";
    for (const auto& p : points) {
        file << p.time << "," << p.x << "," << p.y << "," << p.z << "," << p.speed << "\n";
    }
    file.close();
    return true;
}

bool TrajectoryLogger::loadFromCSV() {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    points.clear();
    std::string line;
    std::getline(file, line); // заголовок
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Point p;
        char comma;
        ss >> p.time >> comma >> p.x >> comma >> p.y >> comma >> p.z >> comma >> p.speed;
        points.push_back(p);
    }
    file.close();
    return true;
}

double TrajectoryLogger::calculateTotalDistance() {
    double total = 0.0;
    for (size_t i = 1; i < points.size(); ++i) {
        double dx = points[i].x - points[i - 1].x;
        double dy = points[i].y - points[i - 1].y;
        double dz = points[i].z - points[i - 1].z;
        total += sqrt(dx * dx + dy * dy + dz * dz);
    }
    return total;
}

double TrajectoryLogger::findMaxSpeed() {
    double maxSpeed = 0.0;
    for (const auto& p : points) {
        if (p.speed > maxSpeed) maxSpeed = p.speed;
    }
    return maxSpeed;
}

void TrajectoryLogger::printStatistics() {
    std::cout << "Total points: " << points.size() << "\n";
    std::cout << "Total distance: " << calculateTotalDistance() << "\n";
    std::cout << "Max speed: " << findMaxSpeed() << "\n";
}