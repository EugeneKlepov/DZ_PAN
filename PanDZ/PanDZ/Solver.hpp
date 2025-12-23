#pragma once
#include "Trajectory.hpp"
#include "StartingConditions.hpp"
#include "Aircraft.hpp"
#include "vector"
#include "array"

enum ManeuverType
{
    Acceleration,
    Lift,
    LiftAcceleration,
    Invalid
};
struct Maneuver
{
    double Time, Fuel;
    bool valid;
    double alpha;
    double tc;//thrust control
};
struct GridData
{
    double Time, Fuel;
    double V, H;
    Maneuver ta, tl, tal;
    Maneuver fa, fl, fal;
    ManeuverType OptimalManeuver, OptimalFuelManeuver;
};

class Solver
{
public:
    Solver();
    Solver(StartingConditions SC, AircraftData* ad, int GridSizeV, int GridSizeH);
    ~Solver();

    void GenerateGrid(StartingConditions SC, AircraftData* ad, int GridSizeV, int GridSizeH);

    Maneuver LiftTime(AircraftData* ad, double V, double H1, double H2, double ThrustControl);
    Maneuver AccelTime(AircraftData* ad, double V1, double V2, double H, double ThrustControl);
    Maneuver LiftAccelTime(AircraftData* ad, double V1, double V2, double H1, double H2, double ThrustControl);

    void CalculateTrajectories();
    // void CalculateTrajectories2();//useless

    Trajectory GetOptimalTimeTrajectory();
    Trajectory GetOptimalFuelTrajectory();

    void Free();

    void PrintVH();
    void PrintManeuverTimeTables();
    void PrintCostTable();
    // void PrintDetailedCostTables();
    void PrintTimeTrajectory();
    void PrintFuelTrajectory();

private:
    
    std::vector<std::vector<GridData>> Grid_;

    int vSteps_, hSteps_;
    int GridSizeV_, GridSizeH_;
    double vStep_, hStep_;
};


