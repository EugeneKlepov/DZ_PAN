#include "Environment.hpp"

Environment::Environment() 
{
    initializeTableData();
}

Environment& Environment::Get() // SINGLETON
{
    static Environment instance;
    return instance; 
}
void Environment::initializeTableData() {
    altitudes = {0, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    temperatures = {288.15, 284.9, 281.651, 275.154, 268.659, 262.166, 255.676,
                    249.187, 242.7, 236.215, 229.733, 223.252};
    pressures = {1.01325e5, 9.54613e4, 8.98763e4, 7.95014e4, 7.01212e4, 6.16604e4,
                5.40483e4, 4.72176e4, 4.11051e4, 3.56516e4, 3.08007e4, 2.64999e4};
    densities = {1.22500, 1.16727, 1.11166, 1.00655, 0.909254, 0.819347, 0.736429,
                0.660111, 0.590018, 0.526783, 0.467063, 0.413510};
    sound_speeds = {340.294, 338.37, 336.435, 332.532, 328.584, 324.589, 320.545,
                    316.452, 312.306, 308.105, 303.848, 299.532};
    gs = {9.8066, 9.8051, 9.8036, 9.8005, 9.7974, 9.7943, 9.7912, 9.7882, 9.7851, 9.7820, 9.7789, 9.7759, 9.7728};
}
double Environment::interpolate(double h, const std::vector<double>& x, const std::vector<double>& y) const{
    if (h <= x[0]) return y[0];
    if (h >= x.back()) return y.back();
    for (size_t i = 0; i < x.size() - 1; ++i) {
        if (h >= x[i] && h <= x[i+1]) {
            double t = (h - x[i]) / (x[i+1] - x[i]);
            return y[i] + t * (y[i+1] - y[i]);
        }
    }
    return y.back();
}
double Environment::Temperature(double h) const { return interpolate(h, altitudes, temperatures); }
double Environment::Pressure(double h) const { return interpolate(h, altitudes, pressures); }
double Environment::Density(double h) const { return interpolate(h, altitudes, densities); }
double Environment::SoundSpeed(double h) const { return interpolate(h, altitudes, sound_speeds); }
double Environment::G(double h) const { return interpolate(h, altitudes, gs); }

double Environment::Mach(double h, double v) const { return v / SoundSpeed(h); }
