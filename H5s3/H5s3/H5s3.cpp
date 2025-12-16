#include <iostream>
#include <vector>
#include <iomanip>

struct Point {
    double x, y, z;
};

int main() {
    double vx = 30.0, vy = 20.0, vz = 40.0;
    double dt = 0.1;
    double t_max = 5.0;

    std::vector<Point> traj;
    traj.reserve(static_cast<size_t>(t_max / dt) + 1);

    double x = 0.0, y = 0.0, z = 0.0;

    for (double t = 0.0; t <= t_max; t += dt) {
        x += vx * dt;
        y += vy * dt;
        z += vz * dt;
        traj.push_back({ x, y, z });
    }

    std::cout << std::setw(10) << "t (c)"
        << std::setw(15) << "x (м)"
        << std::setw(15) << "y (м)"
        << std::setw(15) << "z (м)" << std::endl;
    std::cout << std::string(55, '-') << std::endl;

    double t = 0.0;
    for (const auto& p : traj) {
        std::cout << std::setw(10) << std::fixed << std::setprecision(2) << t
            << std::setw(15) << std::fixed << std::setprecision(2) << p.x
            << std::setw(15) << std::fixed << std::setprecision(2) << p.y
            << std::setw(15) << std::fixed << std::setprecision(2) << p.z << std::endl;
        t += dt;
    }

    return 0;
}