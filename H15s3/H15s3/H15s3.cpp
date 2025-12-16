#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> x_coords = { 10.5, 5.2, 10.5, 8.1, 5.2, 12.3, 8.1, 15.0 };

    std::cout << "Исходные координаты X: ";
    for (double x : x_coords) std::cout << x << " ";
    std::cout << std::endl;

    // Сортировка
    std::sort(x_coords.begin(), x_coords.end());

    std::cout << "После сортировки: ";
    for (double x : x_coords) std::cout << x << " ";
    std::cout << std::endl;

    // Удаление дубликатов
    auto last = std::unique(x_coords.begin(), x_coords.end());
    x_coords.erase(last, x_coords.end());

    std::cout << "После удаления дубликатов: ";
    for (double x : x_coords) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}