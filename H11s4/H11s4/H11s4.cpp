#include <iostream>
#include <iomanip>
using namespace std;

// 1. Класс Engine
class Engine {
private:
    double thrust;
    double fuelFlow;
    double fuel;

public:
    Engine(double thr, double flow, double f)
        : thrust(thr), fuelFlow(flow), fuel(f) {
    }

    double getThrust() const {
        return thrust;
    }

    bool hasFuel() const {
        return fuel > 0;
    }

    void burn(double dt) {
        if (hasFuel()) {
            double consumed = fuelFlow * dt;
            if (consumed > fuel) consumed = fuel;
            fuel -= consumed;
        }
    }

    double getFuel() const {
        return fuel;
    }
};

// 2. Класс Navigation
class Navigation {
private:
    double altitude;
    double velocity;
    double acceleration;
    double mass;

public:
    Navigation(double alt, double vel, double m)
        : altitude(alt), velocity(vel), mass(m), acceleration(0) {
    }

    void update(double thrust, double dt) {
        acceleration = thrust / mass - 9.81;
        velocity += acceleration * dt;
        altitude += velocity * dt;
        if (altitude < 0) altitude = 0;
    }

    void printStatus(double time) const {
        cout << fixed << setprecision(2);
        cout << "t=" << time << "с | h=" << altitude
            << "м | v=" << velocity << "м/с | a=" << acceleration << "м/с²" << endl;
    }

    double getAltitude() const {
        return altitude;
    }
};

// 3. Класс AutonomousFlightSystem
class AutonomousFlightSystem {
private:
    Engine engine;
    Navigation nav;
    double time;

public:
    AutonomousFlightSystem(const Engine& e, const Navigation& n)
        : engine(e), nav(n), time(0) {
    }

    void simulate(double dt, double totalTime) {
        while (time < totalTime && engine.hasFuel()) {
            engine.burn(dt);
            nav.update(engine.getThrust(), dt);
            nav.printStatus(time);
            time += dt;
        }
    }

    void printSummary() const {
        cout << "--- Полет завершен ---" << endl;
        cout << "Оставшееся топливо: " << engine.getFuel() << " кг" << endl;
        cout << "Итоговая высота: " << nav.getAltitude() << " м" << endl;
    }
};

int main() {
    Engine engine(12000, 2.5, 50);   // тяга, расход, топливо
    Navigation nav(0, 0, 1000);      // высота, скорость, масса
    AutonomousFlightSystem system(engine, nav);

    system.simulate(1.0, 10.0);
    system.printSummary();

    return 0;
}