#include <iostream>
using namespace std;

class Gyroscope {
private:
    double angularVelocity;
    bool calibrationRequired;

public:
    Gyroscope(double vel, bool cal)
        : angularVelocity(vel), calibrationRequired(cal) {
    }

    void calibrate() {
        calibrationRequired = false;
    }

    void printStatus() const {
        cout << "Скорость: " << angularVelocity << " °/с | "
            << "Калибровка " << (calibrationRequired ? "требуется" : "не требуется") << endl;
    }
};

int main() {
    Gyroscope g1(120.5, true);
    g1.printStatus();
    g1.calibrate();
    g1.printStatus();

    return 0;
}