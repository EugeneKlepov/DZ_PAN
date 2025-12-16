#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> heights = { 15.0, 5.0, 25.0, 8.0, 30.0, 2.0, 12.0 };

    std::cout << "Исходные высоты: ";
    for (double h : heights) std::cout << h << " ";
    std::cout << std::endl;

    auto new_end = std::remove_if(heights.begin(), heights.end(),
        [](double h) { return h < 10.0; });

    heights.erase(new_end, heights.end());

    std::cout << "После удаления значений < 10: ";
    for (double h : heights) std::cout << h << " ";
    std::cout << std::endl;

    return 0;
}