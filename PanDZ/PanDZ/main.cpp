#include <iostream>
#include <cmath>
#include <print>

#include <Aircraft.hpp>
#include <TU154.hpp>
#include <Solver.hpp>
#include <StartingConditions.hpp>

int main(void)
{
    StartingConditions sc =
    {
        .p_percent = 100.0,
        .v_start_kmh = 320.0,
        .v_end_kmh = 900.0,
        .h_start_m = 400.0,
        .h_end_m = 6500.0,
    };
    TU154 aircraft(sc);
    AircraftData* Data = &aircraft;

    Solver solver;
    solver.GenerateGrid(sc, Data, 50, 50);
    solver.CalculateTrajectories();

    // solver.PrintVH();
    // solver.PrintManeuverTimeTables();
    // solver.PrintCostTable();
    solver.PrintTimeTrajectory();
    solver.PrintFuelTrajectory();

    Trajectory OptimalTimeT = solver.GetOptimalTimeTrajectory();
    OptimalTimeT.GenerateCSV("hv.csv", "alpha.csv");
    std::println("{}", OptimalTimeT.GetTotalTime());
    std::println("{}", OptimalTimeT.GetTotalFuelConsumed());
    OptimalTimeT.GenerateGPLOTScript("time","hv.csv", "alpha.csv");

    Trajectory OptimalFuelT = solver.GetOptimalFuelTrajectory();
    OptimalFuelT.GenerateCSV("hv2.csv", "alpha2.csv");
    std::println("{}", OptimalFuelT.GetTotalTime());
    std::println("{}", OptimalFuelT.GetTotalFuelConsumed());
    OptimalFuelT.GenerateGPLOTScript("fuel", "hv2.csv", "alpha2.csv");

    return 0;
}




