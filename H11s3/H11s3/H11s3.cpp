#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
    std::vector<double> heights = { 0.0, 45.2, 80.5, 85.1, 70.3, 30.8, -5.0 };
    std::vector<double> times = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    if (heights.empty()) {
        std::cout << "Нет данных" << std::endl;
        return 0;
    }

    auto max_it = std::max_element(heights.begin(), heights.end());
    size_t idx = std::distance(heights.begin(), max_it);

    std::cout << "Максимальная высота: " << *max_it
        << " м в момент времени " << times[idx] << " с" << std::endl;

    return 0;
}
