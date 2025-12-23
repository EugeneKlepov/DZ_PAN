#include <iostream>
#include <cmath>
#include <print>

#include "Aircraft.hpp"
#include "IL76.hpp"
#include "Solver.hpp"
#include "StartingConditions.hpp"

int main(void)
{
    StartingConditions sc =
    {
        .p_percent = 100.0,
        .v_start_kmh = 300.0,
        .v_end_kmh = 750.0,
        .h_start_m = 300.0,
        .h_end_m = 5000.0,
    };
    IL76 aircraft(sc);
    AircraftData* Data = &aircraft;

    Solver solver;
    solver.GenerateGrid(sc, Data, 20, 20);
    solver.CalculateTrajectories();

    Trajectory OptimalTimeT = solver.GetOptimalTimeTrajectory();
    OptimalTimeT.GenerateCSV("hv.csv", "alpha.csv");
    std::println("{}", OptimalTimeT.GetTotalTime());
    std::println("{}", OptimalTimeT.GetTotalFuelConsumed());
    OptimalTimeT.GenerateGPLOTScript("time", "hv.csv", "alpha.csv");

    Trajectory OptimalFuelT = solver.GetOptimalFuelTrajectory();
    OptimalFuelT.GenerateCSV("hv2.csv", "alpha2.csv");
    std::println("{}", OptimalFuelT.GetTotalTime());
    std::println("{}", OptimalFuelT.GetTotalFuelConsumed());
    OptimalFuelT.GenerateGPLOTScript("fuel", "hv2.csv", "alpha2.csv");

    std::system("gnuplot timeplothv.gp -p");
    std::system("gnuplot fuelplothv.gp -p");
    std::system("gnuplot timeplotalpha.gp -p");
    std::system("gnuplot fuelplotalpha.gp -p");

    std::cin.get();
    return 0;
}

