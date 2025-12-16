#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> heights1 = { 0, 45, 80, 85, 70, 30, -10 };
    std::vector<double> times1 = { 0, 1, 2, 3, 4, 5, 6 };

    std::vector<double> heights2 = { 0, 40, 75, 90, 65, 25, -5 };
    std::vector<double> times2 = { 0, 1, 2, 3, 4, 5, 6 };

    auto max_it1 = std::max_element(heights1.begin(), heights1.end());
    auto max_it2 = std::max_element(heights2.begin(), heights2.end());

    size_t idx_max1 = std::distance(heights1.begin(), max_it1);
    size_t idx_max2 = std::distance(heights2.begin(), max_it2);

    std::cout << "Ракета 1: max h = " << *max_it1 << " м в t = " << times1[idx_max1] << " с" << std::endl;
    std::cout << "Ракета 2: max h = " << *max_it2 << " м в t = " << times2[idx_max2] << " с" << std::endl;

    if (*max_it1 > *max_it2) std::cout << "Ракета 1 выше" << std::endl;
    else if (*max_it2 > *max_it1) std::cout << "Ракета 2 выше" << std::endl;
    else std::cout << "Высоты равны" << std::endl;

    auto fall_it1 = std::find_if(heights1.begin(), heights1.end(),
        [](double h) { return h <= 0; });
    auto fall_it2 = std::find_if(heights2.begin(), heights2.end(),
        [](double h) { return h <= 0; });

    if (fall_it1 != heights1.end() && fall_it2 != heights2.end()) {
        size_t idx_fall1 = std::distance(heights1.begin(), fall_it1);
        size_t idx_fall2 = std::distance(heights2.begin(), fall_it2);

        if (times1[idx_fall1] > times2[idx_fall2]) std::cout << "Ракета 1 дольше в воздухе" << std::endl;
        else if (times2[idx_fall2] > times1[idx_fall1]) std::cout << "Ракета 2 дольше в воздухе" << std::endl;
        else std::cout << "Время падения одинаково" << std::endl;
    }

    return 0;
}