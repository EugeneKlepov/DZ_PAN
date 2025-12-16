#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> temperatures = { 150.0, 180.0, -150.0, 190.0, 250.0, 80.0, -200.0, 170.0 };

    std::cout << "Исходные данные: ";
    for (double t : temperatures) std::cout << t << " ";
    std::cout << std::endl;

    temperatures.erase(
        std::remove_if(temperatures.begin(), temperatures.end(),
            [](double t) { return t < -100.0 || t > 200.0; }),
        temperatures.end()
    );

    std::cout << "Очищенные данные: ";
    for (double t : temperatures) std::cout << t << " ";
    std::cout << std::endl;

    return 0;
}