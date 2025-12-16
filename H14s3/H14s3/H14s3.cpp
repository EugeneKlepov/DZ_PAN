#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <iomanip>

int main() {
    std::vector<double> positions = { 0.0, 10.5, 25.3, 45.8, 70.2, 100.0 };

    // Разности между соседними позициями
    std::vector<double> displacements(positions.size());
    std::adjacent_difference(positions.begin(), positions.end(), displacements.begin());

    std::cout << "Смещения на каждом шаге: ";
    for (size_t i = 1; i < displacements.size(); ++i) {
        std::cout << std::fixed << std::setprecision(2) << displacements[i] << " ";
    }
    std::cout << std::endl;

    // Суммируем абсолютные значения смещений (игнорируем первый элемент - он равен positions[0])
    double total_path = 0.0;
    for (size_t i = 1; i < displacements.size(); ++i) {
        total_path += std::abs(displacements[i]);
    }

    std::cout << "Суммарный путь: " << std::fixed << std::setprecision(2)
        << total_path << " м" << std::endl;

    return 0;
}