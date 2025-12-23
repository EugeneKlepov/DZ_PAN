#include "Trajectory.hpp"
#include "Solver.hpp"
#include "Environment.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iterator>
#include <print>
Solver::Solver()
{

}
Solver::Solver(StartingConditions SC, AircraftData* ad, int GridSizeV, int GridSizeH)
{
    GenerateGrid(SC, ad, GridSizeV, GridSizeH);
}
Solver::~Solver(){}

void Solver::GenerateGrid(StartingConditions SC, AircraftData* ad, int GridSizeV, int GridSizeH)
{
    GridSizeH_ = GridSizeH;
    GridSizeV_ = GridSizeV;
    hSteps_ = GridSizeH_-1;
    vSteps_ = GridSizeV_-1;
    vStep_ = fabs(SC.v_end_kmh-SC.v_start_kmh)*1000.0/3600.0/vSteps_;
    hStep_ = fabs(SC.h_end_m-SC.h_start_m)/hSteps_;
    double dV = vStep_;
    double dH = hStep_;

    Grid_.resize(GridSizeV);
    for(int i = 0; i < GridSizeV; i++)
    {
        Grid_[i].resize(GridSizeH);
        double V = SC.v_start_kmh*1000.0/3600.0+i*dV;
        Maneuver im = {9999.9, 9999.9, false, 0.};
        Grid_[i].resize(GridSizeH);
        for(int j = 0; j < GridSizeH; j++)
        {
            auto& p = Grid_[i][j];
            double H = SC.h_start_m+j*dH;
            p.Time = 9999.9;
            p.Fuel = 99999999.9;
            
            p.V = V;
            p.H = H;
            p.ta = im;
            p.tal = im;
            p.tl = im;
            p.fa = im;
            p.fal = im;
            p.fl = im;

            double ThrustPercent[] = {1.0, 0.95, 0.9, 0.85, 0.8, 0.75, 0.7, 0.65, 0.6, 0.55, 0.5, 0.4, 0.3, 0.2};
            // double TestTP[] = {1.0};
            for(auto& tc: ThrustPercent)
            // for(auto& tc: TestTP)
            {
                if(i < vSteps_)
                {
                    Maneuver m = AccelTime(ad, V, V+dV, H, tc);
                    // std::println("{}, {}", m.Time, Grid_[i][j].ta.Time);
                    if(m.Time < Grid_[i][j].ta.Time && m.valid)
                    {
                        m.tc = tc;
                        Grid_[i][j].ta = m;
                    }
                    if(m.Fuel < Grid_[i][j].fa.Fuel && m.valid)
                    {
                        m.tc = tc;
                        Grid_[i][j].fa = m;
                    }
                }
                if(j < hSteps_)
                {
                    Maneuver m = LiftTime(ad, V, H, H+dH, tc);
                    if(m.Time < Grid_[i][j].tl.Time && m.valid)
                    {
                        m.tc = tc;
                        Grid_[i][j].tl = m;
                    }
                    if(m.Fuel < Grid_[i][j].fl.Fuel && m.valid)
                    {
                        m.tc = tc;
                        Grid_[i][j].fl = m;
                    }
                }
                if(i < vSteps_ && j < hSteps_)
                {
                    Maneuver m = LiftAccelTime(ad, V, V+dV, H, H+dH, tc);
                    if(m.Time < Grid_[i][j].tal.Time && m.valid)
                    {
                        m.tc = tc;
                        Grid_[i][j].tal = m;
                    }
                    if(m.Fuel < Grid_[i][j].fal.Fuel && m.valid)
                    {
                        m.tc = tc;
                        Grid_[i][j].fal = m;
                    }
                }
                // Maneuver ml = LiftTime(ad, V, H, H+dH, tc);
                // Maneuver mla = LiftAccelTime(ad, V, V+dV, H, H+dH, tc);

            }
        }
    }
}
void Solver::CalculateTrajectories()
{   
    for(int j = GridSizeH_-1; j >= 0; j--)
    {
        for(int i = GridSizeV_-1; i >= 0; i--)
        {
            auto& p = Grid_[i][j];
            // std::println("{},{}", p.V, p.H);
            if((i==GridSizeV_-1)&&(j==GridSizeH_-1))
            {
                p.Time=0.0;
                p.Fuel=0.0;
            }
            if(i<GridSizeV_-1)
            {
                auto& pi = Grid_[i+1][j];
                double t = pi.Time + p.ta.Time;
                double f = pi.Fuel + p.fa.Fuel;
                // std::println("{},{}", t, p.Time);
                if(p.Time > t && p.ta.valid)
                {
                    p.Time = t;
                    p.OptimalManeuver = Acceleration;
                }
                if(p.Fuel > f && p.fa.valid)
                {
                    p.Fuel = f;
                    p.OptimalFuelManeuver = Acceleration;
                }
            }
            if(j<GridSizeH_-1)
            {
                
                auto& pj = Grid_[i][j+1];
                double t = pj.Time + p.tl.Time;
                double f = pj.Fuel + p.fl.Fuel;
                // std::println("{},{}", t, p.Time);
                if(p.Time > t && p.tl.valid)
                {
                    p.Time = t;
                    p.OptimalManeuver = Lift;
                }
                if(p.Fuel > f && p.fl.valid)
                {
                    p.Fuel = f;
                    p.OptimalFuelManeuver = Lift;
                }
            }
            if(i<GridSizeV_-1 && j<GridSizeH_-1)
            {
                auto& pij = Grid_[i+1][j+1];
                double t = pij.Time + p.tal.Time;
                double f = pij.Fuel + p.fal.Fuel;
                if(p.Time > t && p.tal.valid)
                {
                    p.Time = t;
                    p.OptimalManeuver = LiftAcceleration;
                }
                if(p.Fuel > f && p.fal.valid)
                {
                    p.Fuel = f;
                    p.OptimalFuelManeuver = LiftAcceleration;
                }
            }
        }
    }
    
}
// void Solver::CalculateTrajectories2()
// {   
//     for(int j = 0; j < GridSizeH_; j++)
//     {
//         for(int i = 0; i < GridSizeV_; i++)
//         {
//             auto& p = Grid_[i][j];
//             // std::println("{},{}", p.V, p.H);
//             if((i==0)&&(j==0))
//             {
//                 p.Time=0.0;
//                 p.Fuel=0.0;
//             }
//             if(i>0)
//             {
//                 auto& pi = Grid_[i-1][j];
//                 double t = pi.Time + pi.ta.Time;
//                 // std::println("{},{}", t, p.Time);
//                 if(p.Time > t && pi.ta.valid)
//                 {
//                     p.Time = t;
//                     pi.OptimalManeuver = Acceleration;
//                 }
//             }
//             if(j>0)
//             {
//                 auto& pj = Grid_[i][j-1];
//                 double t = pj.Time + pj.tl.Time;
//                 if(p.Time > t && pj.tl.valid)
//                 {
//                     p.Time = t;
//                     pj.OptimalManeuver = Lift;
//                 }
//             }
//             if(i>0 && j>0)
//             {
//                 auto& pij = Grid_[i-1][j-1];
//                 double t = pij.Time + pij.tal.Time;
//                 if(p.Time > t && pij.tal.valid)
//                 {
//                     p.Time = t;
//                     pij.OptimalManeuver = LiftAcceleration;
//                 }
//             }
//         }
//     }
//
// }
Maneuver Solver::LiftTime(AircraftData* ad, double V, double H1, double H2, double ThrustControl)
{
    double dH = (H2-H1);
    double H = (H2+H1)/2.0;
    double g = Environment::Get().G(H);
    double mass = ad->StartMass();
    double AlphaRad = ad->AlphaRad(V, H, mass);
    double P = ad->TotalThrust(V, H, mass) * ThrustControl;
    double X = ad->X(V, H, AlphaRad);
    if(P*cos(AlphaRad) < X) return {0.,0.,false,0.};
    double theta = (P*cos(AlphaRad)-X)/(mass*g);

    double dt = dH/(V*sin(theta));

    double Cp = ad->Cp(V, H, ThrustControl);
    double dm = Cp*P*dt/3600.0;

    return {dt, dm, true, AlphaRad, ThrustControl};
}
Maneuver Solver::AccelTime(AircraftData* ad, double V1, double V2, double H, double ThrustControl)
{
    double dV = (V2-V1);
    double V = (V2+V1)/2.0;
    double mass = ad->StartMass();
    double P = ad->TotalThrust(V, H, mass) * ThrustControl;
    double Alpha = ad->AlphaRad(V, H, mass);
    double X = ad->X(V, H, Alpha);
    if(P*cos(Alpha) < X) return {0.,0.,false,0.};
    double a = (P*cos(Alpha)-X)/mass;

    double dt = dV/a;

    double Cp = ad->Cp(V, H, ThrustControl);
    double dm = Cp*P*dt/3600.0;

    return {dt, dm, true, Alpha, ThrustControl};
}
Maneuver Solver::LiftAccelTime(AircraftData* ad, double V1, double V2, double H1, double H2, double ThrustControl)
{
    double dV = (V2-V1);
    double dH = (H2-H1);
    double H = (H2+H1)/2.0;
    double V = (V2+V1)/2.0;
    double mass = ad->StartMass();
    double P = ad->TotalThrust(V, H, mass) * ThrustControl;
    double g = Environment::Get().G(H);
    double Alpha = ad->AlphaRad(V, H, mass);
    double X = ad->X(V, H, Alpha);
    if(P*cos(Alpha) < X) return {0.,0.,false,0., ThrustControl};
    double C = dV/dH;
    double theta = (P-X)/(mass*C*V+mass*g);

    double dt = 1/(C*sin(theta))*log(V2/V1);

    double Cp = ad->Cp(V, H, ThrustControl);
    double dm = Cp*P*dt/3600.0;

    return {dt, dm, true, Alpha};
}



void Solver::PrintVH()
{
    for(int j = GridSizeH_-1; j >= 0; j--)
    {
        for(int i = 0; i < GridSizeV_; i++)
        {
            auto& p = Grid_[i][j];
            std::print("{:>8.1f}/{:<8.1f} ", p.V/1000.0*3600.0, p.H);
        }
        std::println();
    }
}
void Solver::PrintCostTable()
{
    std::println("Матрица затрат");
    for(int j = GridSizeH_-1; j >= 0; j--)
    {
        for(int i = 0; i < GridSizeV_; i++)
        {
            auto& p = Grid_[i][j];
            std::print("{:>8.1f}/{:<8.1f} ", p.Time, p.Fuel);
        }
        std::println();
    }
}

void Solver::PrintManeuverTimeTables()
{
    std::println("Матрица разгона по времени");
    for(int j = GridSizeH_-1; j >= 0; j--)
    {
        for(int i = 0; i < GridSizeV_; i++)
        {
            auto& p = Grid_[i][j];
            std::print("{:>8.1f} ", p.ta.Time);
        }
        std::println();
    }
    std::println("Матрица подъема по времени");
    for(int j = GridSizeH_-1; j >= 0; j--)
    {
        for(int i = 0; i < GridSizeV_; i++)
        {
            auto& p = Grid_[i][j];
            std::print("{:>8.1f} ", p.tl.Time);
        }
        std::println();
    }
    std::println("Матрица разгон-подъема по времени"); for(int j = GridSizeH_-1; j >= 0; j--)
    {
        for(int i = 0; i < GridSizeV_; i++)
        {
            auto& p = Grid_[i][j];
            std::print("{:>8.1f} ", p.tal.Time);
        }
        std::println(); 
    }
}

void Solver::PrintTimeTrajectory()
{   
    for(int j = GridSizeH_-1; j >= 0; j--)
    {
        for(int i = 0; i < GridSizeV_; i++)
        {
            auto& p = Grid_[i][j];
            std::string s = "x";
            if(p.OptimalManeuver == Lift)
            {s = "|";}
            if(p.OptimalManeuver == Acceleration)
            {s = "-";}
            if(p.OptimalManeuver == LiftAcceleration)
            {s = "/";}
            std::print("{} ", s);
        }
        std::println();
    }
}
void Solver::PrintFuelTrajectory()
{   
    for(int j = GridSizeH_-1; j >= 0; j--)
    {
        for(int i = 0; i < GridSizeV_; i++)
        {
            auto& p = Grid_[i][j];
            std::string s = "x";
            if(p.OptimalFuelManeuver == Lift)
            {s = "|";}
            if(p.OptimalFuelManeuver == Acceleration)
            {s = "-";}
            if(p.OptimalFuelManeuver == LiftAcceleration)
            {s = "/";}
            std::print("{} ", s);
        }
        std::println();
    }
    
}

Trajectory Solver::GetOptimalTimeTrajectory()
{
    int i = 0, j = 0;
    Trajectory t;
    while(i!=GridSizeV_-1 && j!=GridSizeH_-1)
    {
        auto& p = Grid_[i][j];
        if(p.OptimalManeuver == Acceleration)
        {
            t.PushBack({{p.H}, p.V, p.ta.alpha, p.ta.Time, p.ta.Fuel, p.ta.tc});
            i++; 
            continue;
        }
        if(p.OptimalManeuver == Lift)
        {
            t.PushBack({{p.H}, p.V, p.tl.alpha, p.tl.Time, p.tl.Fuel, p.tl.tc});
            j++; 
            continue;
        }
        if(p.OptimalManeuver == LiftAcceleration)
        {
            t.PushBack({{p.H}, p.V, p.tal.alpha, p.tal.Time, p.tal.Fuel, p.tal.tc});
            i++; 
            j++;
            continue;
        }
    }
    return t;
}

Trajectory Solver::GetOptimalFuelTrajectory()
{
    int i = 0, j = 0;
    Trajectory t;
    while(i!=GridSizeV_-1 || j!=GridSizeH_-1)
    {
        auto& p = Grid_[i][j];
        if(p.OptimalFuelManeuver == Acceleration)
        {
            t.PushBack({{p.H}, p.V, p.fa.alpha, p.fa.Time, p.fa.Fuel, p.fa.tc});
            i++; 
            continue;
        }
        if(p.OptimalFuelManeuver == Lift)
        {
            t.PushBack({{p.H}, p.V, p.fl.alpha, p.fl.Time, p.fl.Fuel, p.fl.tc});
            j++; 
            continue;
        }
        if(p.OptimalFuelManeuver == LiftAcceleration)
        {
            t.PushBack({{p.H}, p.V, p.fal.alpha, p.fal.Time, p.fal.Fuel, p.fal.tc});
            i++; 
            j++;
            continue;
        }
    }
    return t;
}
