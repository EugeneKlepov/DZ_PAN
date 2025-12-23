#pragma once
#include <print>
#include <functional>

class AircraftData
{
public:
    AircraftData();
    ~AircraftData();
    virtual double Cx(double Cy) = 0;
    virtual double Cy(double alpha_rad) = 0;
    virtual double X(double V, double H, double alpha_rad) = 0;
    virtual double Y(double V, double H, double alpha_rad) = 0;
    virtual double EngineThrust(double V, double H [[maybe_unused]]) = 0;
    virtual double TotalThrust(double V, double H, double mass) = 0;
    virtual double Cp(double V, double H, double tc[[maybe_unused]]) = 0;
    virtual double AlphaRad(double v, double h, double m) = 0;//returns in radians
    double EngineCount() const;
    double StartMass() const;
    double WingArea() const;
    
protected:
    double wing_area_;
    double start_mass_;

    double Cy0_, Cyk_;
    double Cp_;
    double PP_;
    double EngineCount_;   
};

