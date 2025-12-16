#include <iostream>
#include <iomanip>
using namespace std;

class FlightComputer {
private:
    double altitude;
    double velocity;
    double fuel;
    double thrust;

public:
    FlightComputer(double alt, double vel, double f, double thr)
        : altitude(alt), velocity(vel), fuel(f), thrust(thr) {
    }

    void simulateStep(double dt) {
        velocity += (thrust / 1000 - 9.8) * dt;
        altitude += velocity * dt;
        fuel -= dt * 2;
        if (fuel < 0) fuel = 0;
    }

    void printStatus(double time) const {
        cout << fixed << setprecision(1);
        cout << "t=" << time << "с: высота=" << altitude
            << "м, скорость=" << velocity << "м/с, топливо=" << fuel << "кг" << endl;
    }
};

int main() {
    FlightComputer fc(0, 0, 100, 12000);
    double time = 0;
    double dt = 0.5;

    for (int i = 0; i < 5; i++) {
        fc.simulateStep(dt);
        time += dt;
        fc.printStatus(time);
    }

    return 0;
}
