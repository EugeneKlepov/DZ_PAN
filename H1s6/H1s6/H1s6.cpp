#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class TrajectoryLogger {
private:
    struct Point {
        double x, y, z, speed, time;
    };
    vector<Point> points;
    string filename;

public:
    TrajectoryLogger(const string& filename) : filename(filename) {}

    void addPoint(double x, double y, double z, double speed, double time) {
        points.push_back({ x, y, z, speed, time });
    }

    bool saveToCSV() {
        ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        file << "time,x,y,z,speed\n";
        for (const auto& p : points) {
            file << p.time << "," << p.x << "," << p.y << "," << p.z << "," << p.speed << "\n";
        }

        file.close();
        return true;
    }

    bool loadFromCSV() {
        points.clear();
        ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        string header;
        getline(file, header);

        double time, x, y, z, speed;
        char comma;
        while (file >> time >> comma >> x >> comma >> y >> comma >> z >> comma >> speed) {
            points.push_back({ x, y, z, speed, time });
        }

        file.close();
        return true;
    }

    double calculateTotalDistance() {
        double total = 0.0;
        for (size_t i = 1; i < points.size(); ++i) {
            double dx = points[i].x - points[i - 1].x;
            double dy = points[i].y - points[i - 1].y;
            double dz = points[i].z - points[i - 1].z;
            total += sqrt(dx * dx + dy * dy + dz * dz);
        }
        return total;
    }

    double findMaxSpeed() {
        double maxSpeed = 0.0;
        for (const auto& p : points) {
            if (p.speed > maxSpeed) {
                maxSpeed = p.speed;
            }
        }
        return maxSpeed;
    }

    void printStatistics() {
        cout << "Total distance: " << calculateTotalDistance() << "\n";
        cout << "Max speed: " << findMaxSpeed() << "\n";
    }
};

int main() {
    TrajectoryLogger logger("trajectory.csv");

    logger.addPoint(10.5, 20.3, 100.0, 25.0, 0.0);
    logger.addPoint(15.2, 25.1, 105.0, 27.5, 1.5);
    logger.addPoint(20.8, 30.7, 110.0, 30.0, 3.0);

    logger.saveToCSV();
    logger.printStatistics();

    return 0;
}