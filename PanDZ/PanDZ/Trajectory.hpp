#pragma once
#include <string>
#include <vector>

class TrajectoryPoint
{
public:
    union
    {
        double H, y;
    };
    double V;   

    double alpha;
    double time_spent, fuel_consumed;
    double tc;//thrust control
    //данные текущией точки + последующего маневра
};

class Trajectory
{
public:
    Trajectory();
    ~Trajectory();
    void PushBack(TrajectoryPoint tp);
    double GetTotalTime();
    double GetTotalFuelConsumed();
    void GenerateCSV(const std::string& file1, const std::string& file2);
    void Delete();

    void GenerateGPLOTScript(const std::string& file_prefix, const std::string& hvcsv, const std::string& acsv);
private:
    double total_time, total_fuel;
    std::vector<TrajectoryPoint> Points;
    std::vector<std::pair<double, double>> Alphas;
};
