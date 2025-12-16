#include <iostream>
using namespace std;

class Sensor {
private:
    double signalStrength;
    bool isActive;

public:
    Sensor(double strength) {
        setSignalStrength(strength);
        activate();
    }

    void activate() {
        isActive = true;
    }

    void deactivate() {
        isActive = false;
    }

    void setSignalStrength(double s) {
        if (s < 0) {
            signalStrength = 0;
        }
        else {
            signalStrength = s;
        }
    }

    double getSignalStrength() const {
        return signalStrength;
    }

    void printStatus() const {
        cout << "Датчик " << (isActive ? "активен" : "выключен")
            << " | Сила сигнала: " << signalStrength << " дБ" << endl;
    }
};

int main() {
    Sensor s1(45.5);
    s1.printStatus();

    s1.setSignalStrength(-10);
    s1.printStatus();

    s1.deactivate();
    s1.printStatus();

    return 0;
}
