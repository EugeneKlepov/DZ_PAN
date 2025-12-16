#include <iostream>
#include <vector>
#include <iomanip>
#include <random>

int main() {
    std::vector<double> h = { 10.2, 11.5, 12.8, 10.9, 13.2, 14.5, 12.1, 11.8, 13.9, 15.2 };

    std::cout << "Исходные данные: ";
    for (double val : h) std::cout << std::setw(6) << std::fixed << std::setprecision(1) << val;
    std::cout << std::endl;

    std::vector<double> smoothed(h.size());

    smoothed[0] = h[0];
    smoothed[h.size() - 1] = h[h.size() - 1];

    for (size_t i = 1; i + 1 < h.size(); ++i) {
        smoothed[i] = (h[i - 1] + h[i] + h[i + 1]) / 3.0;
    }

    std::cout << "Сглаженные данные: ";
    for (double val : smoothed) std::cout << std::setw(6) << std::fixed << std::setprecision(1) << val;
    std::cout << std::endl;

    return 0;
}