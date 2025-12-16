#include <iostream>
#include <vector>
#include <iomanip>

class Rocket {
private:
    double x, y, z;
    double vx, vy, vz;
public:
    Rocket(double startX, double startY, double startZ, double startVx, double startVy, double startVz)
        : x(startX), y(startY), z(startZ), vx(startVx), vy(startVy), vz(startVz) {
    }

    void updatePosition(double dt) {
        x += vx * dt;
        y += vy * dt;
        z += vz * dt;
    }

    void printPosition() const {
        std::cout << "(" << std::fixed << std::setprecision(2) << x
            << ", " << y << ", " << z << ")" << std::endl;
    }
};

int main() {
    std::vector<Rocket> squad;
    squad.reserve(5);

    squad.emplace_back(0, 0, 0, 30, 10, 50);
    squad.emplace_back(0, 0, 0, 25, 15, 45);
    squad.emplace_back(0, 0, 0, 35, 5, 55);
    squad.emplace_back(0, 0, 0, 28, 12, 48);
    squad.emplace_back(0, 0, 0, 32, 8, 52);

    double dt = 0.1;
    double T = 10.0;

    for (double t = 0; t <= T; t += dt) {
        for (auto& rocket : squad) {
            rocket.updatePosition(dt);
        }
    }

    std::cout << "Конечные положения ракет:" << std::endl;
    for (size_t i = 0; i < squad.size(); ++i) {
        std::cout << "Ракета " << i + 1 << ": ";
        squad[i].printPosition();
    }

    return 0;
}