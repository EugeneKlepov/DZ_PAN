#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> times = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 };
    std::vector<double> heights = { 50.0, 40.2, 20.4, -0.5, -30.0, -80.0 };

    auto it = std::find_if(heights.begin(), heights.end(),
        [](double h) { return h <= 0.0; });

    if (it != heights.end()) {
        size_t idx = std::distance(heights.begin(), it);
        std::cout << "Момент падения: t = " << times[idx]
            << " с, h = " << heights[idx] << " м" << std::endl;
    }
    else {
        std::cout << "Падения не было в диапазоне" << std::endl;
    }

    return 0;
}