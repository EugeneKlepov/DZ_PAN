
#include <iostream> 
#include <vector> 
#include <cmath> 
#include <iomanip>  

int main() {
    setlocale(LC_ALL, "Rus");
    std::vector<double> times;
    std::vector<double> heights;
    double g = 9.8;
    double dt = 0.1;
    double h = 0.0;
    double v0 = 50.0;
    for (double t = 0.0; t <= 5.0; t += dt) {
        h = v0 * t - 0.5 * g * t * t;
        if (h < 0) break;
        times.push_back(t);
        heights.push_back(h);
    }
    // Заголовок таблицы 
    std::cout << std::setw(10) << "t (с)"
        << std::setw(15) << "h (м)"
        << std::endl;
    std::cout << std::string(25, '-') << std::endl;
    // Данные 
    for (size_t i = 0; i < times.size(); i++) {
        std::cout << std::setw(10) << std::fixed << std::setprecision(2) << times[i]
            << std::setw(15) << std::fixed << std::setprecision(2) << heights[i]
            << std::endl;
    }
    return 0;
}