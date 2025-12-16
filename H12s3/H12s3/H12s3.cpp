#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> sensor_data = { 2.5, 0.0, 3.7, 0.0, 0.0, 4.2, 1.8, 0.0, 5.0 };

    int zero_count = std::count(sensor_data.begin(), sensor_data.end(), 0.0);

    std::cout << "Количество нулевых показаний: " << zero_count << std::endl;

    return 0;
}