#pragma once
#include <vector>

class Environment
{
public:
    Environment();
    Environment(const Environment&) = delete;
    void operator= (const Environment&) = delete;
    static Environment& Get();

    double Temperature(double h) const;
    double Pressure(double h) const;
    double Density(double h) const;
    double SoundSpeed(double h) const;
    double Mach(double h, double v) const;
    double G(double h) const;
private:
    std::vector<double> altitudes;
    std::vector<double> temperatures;
    std::vector<double> pressures;
    std::vector<double> densities;
    std::vector<double> sound_speeds;
    std::vector<double> gs;

    void initializeTableData();
    double interpolate(double h, const std::vector<double>& x, const std::vector<double>& y) const;
};
