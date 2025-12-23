#include "IL76.hpp"
#include "Environment.hpp"
#include "StartingConditions.hpp"
#include <cmath>
#define M_PI 3.1415

IL76::IL76(StartingConditions sc)
{
    start_mass_ = 155000;
    EngineCount_ = 4;
    wing_area_ = 300;
    PP_ = sc.p_percent;

    Cy0_ = -0.102;
    Cyk_ = 0.085;
}
IL76::~IL76(){}
double IL76::Cx(double Cy_)
{
    double k = 0.05;

    const double Cx0 = 0.025;
    double Cx = Cx0 + k * Cy_ * Cy_;

    return Cx; 
}
double IL76::Cy(double alpha_rad)
{
    return alpha_rad*180.0/M_PI*Cyk_+Cy0_;
}
double IL76::X(double V, double H, double alpha_rad)
{
    double rho = Environment::Get().Density(H);
    double q = 0.5 * rho * V * V;
    double Cl = Cy(alpha_rad);
    double Cd = Cx(Cl);
    return Cd * wing_area_ * q;

}
double IL76::Y(double V_ms, double H_m, double alpha_rad)
{
    double rho = Environment::Get().Density(H_m);
    double q = 0.5 * rho * V_ms * V_ms;
    double Cl = Cy(alpha_rad);
    return Cl * wing_area_ * q;
}
double IL76::EngineThrust(double V_ms, double H_m)
{
    double M = Environment::Get().Mach(V_ms, H_m);
    double H_km = H_m / 1000.0;
    double P_sea = 58860.0;

    double altitude_factor;
    if (H_km <= 0) {
        altitude_factor = 1.0;
    }
    else if (H_km >= 11.0) {
        altitude_factor = 0.50;
    }
    else {
        altitude_factor = 1.0 - 0.50 * pow(H_km / 11.0, 0.7);
    }

    double mach_factor = 0.88 + 0.24 * M;
    if (mach_factor > 1.08) mach_factor = 1.08;

    return P_sea * altitude_factor * mach_factor * PP_/100.0;
}
double IL76::TotalThrust(double V_ms, double H_m, double mass)
{
    return EngineThrust(V_ms, H_m) * EngineCount_ * mass/StartMass();
}
double IL76::Cp(double V, double H, double tc)
{
    double M = Environment::Get().Mach(V, H);
    double H_km = H / 1000.0;

    double Cp_base = 0.70;

    double regime_factor;
    if (tc >= 1.0) {
        regime_factor = 1.0 + 0.50 * pow(tc - 1.0, 1.3);
    }
    else if (tc >= 0.88) {
        regime_factor = 0.93 - 0.03 * (tc - 0.88) / 0.12;
    }
    else if (tc >= 0.70) {
        regime_factor = 0.93 + 0.10 * pow((0.88 - tc) / 0.18, 1.2);
    }
    else {
        regime_factor = 1.15;
    }

    double altitude_factor = 1.0 - 0.08 * std::min(1.0, H_km / 11.0);
    double mach_factor = 1.0 + 0.15 * std::max(0.0, M - 0.5);

    double Cp = Cp_base * regime_factor * altitude_factor * mach_factor;
    // double Cp = Cp_base * altitude_factor * mach_factor;
    return Cp / 9.81;
}
double IL76::AlphaRad(double V_ms, double H_m, double m)
{
    double rho = Environment::Get().Density(H_m);
    double g = Environment::Get().G(H_m);
    double q = 0.5 * rho * V_ms * V_ms;
    double S = WingArea();
    double P = TotalThrust(V_ms, H_m, m);
    double alpha_deg = (m*g-Cy0_*q*S)/(P+Cyk_*q*S);
    return alpha_deg*M_PI/180.0;
}
