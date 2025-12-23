#pragma once
#include "StartingConditions.hpp"
#include "Aircraft.hpp"

class IL76: public AircraftData
{
public:
    IL76(StartingConditions sc);
    ~IL76();
    double Cx(double Cy) override;
    double Cy(double alpha) override;
    double X(double V_ms, double H_m, double alpha_rad) override;
    double Y(double V_ms, double H_m, double alpha_rad) override;
    double EngineThrust(double V_ms, double H_m) override;
    double TotalThrust(double V_ms, double H_m, double mass) override;
    double Cp(double V_ms, double H_m, double tc[[maybe_unused]]) override;
    double AlphaRad(double V_ms, double H_m, double m) override;
};
