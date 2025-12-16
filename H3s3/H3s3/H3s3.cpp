
#include <iostream> 
#include <vector> 
#include <cmath> 
#include <iomanip>  

int main() {
    setlocale(LC_ALL, "Rus");
    std::vector<double> times;
    std::vector<double> velocities;
    double g = 9.8;
    double dt = 0.1;
    double t_max;
    double v = 0.0;
    std::cout << "Введите t" "\n";
    std::cin >> t_max;
    double v0 = 50.0;
    double vpol = v0 / g;
    for (double t = 0.0; t <= t_max; t += dt) {
        v = v0 - g * t;
        if (v < vpol)break;
        times.push_back(t);
        velocities.push_back(v);
    }
    // Заголовок таблицы 
    std::cout << std::setw(10) << "t (с)"
        << std::setw(15) << "v (м/с)"
        << std::endl;
    std::cout << std::string(25, '-') << std::endl;
    // Данные 
    for (size_t i = 0; i < times.size(); i++) {
        std::cout << std::setw(10) << std::fixed << std::setprecision(2) << times[i]
            << std::setw(15) << std::fixed << std::setprecision(2) << velocities[i]
            << std::endl;

    }
}