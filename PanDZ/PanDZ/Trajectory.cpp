#include "Trajectory.hpp"
#include <fstream>
#include <print>
#include <cmath>
#define M_PI 3.1415
Trajectory::Trajectory()
{

}
Trajectory::~Trajectory()
{

}
void Trajectory::PushBack(TrajectoryPoint tp)
{
    Points.push_back(tp);
}
double Trajectory::GetTotalTime()
{
    double t = 0;
    for(const auto& p: Points)
    {
        t += p.time_spent;
    }
    return t;
    // return total_time;
} 
double Trajectory::GetTotalFuelConsumed()
{
    double f = 0;
    for(const auto& p: Points)
    {
        f += p.fuel_consumed;
        // std::println("{}",p.tc);
    }
    return f;
    // return total_fuel;
}
void Trajectory::GenerateCSV(const std::string& file1, const std::string& file2)
{
    // for(const auto& p: Points)
    // {
    //
    // }
    std::ofstream hv_csv(file1, std::ios::out);
    if(!hv_csv.is_open())
    {
        std::println("Не получилось вывести в файл таблицу точек");
        return;
    }
    hv_csv << std::format("{:>15},{:>15}", "Высоты", "Скорости") << "\n";

    for(const auto& point: Points)
    {
        // std::println("{},{}", point.H, point.V);
        hv_csv << std::format("{:>15.5},{:>15.5}", point.H, point.V*3600.0/1000.0) << "\n";
    }
    //cat trajectory.csv в терминале чтобы проверить вывод
    hv_csv.close();

    std::ofstream alpha_csv(file2, std::ios::out);
    if(!alpha_csv.is_open())
    {
        std::println("Не получилось вывести в файл таблицу альф");
        return;
    }
    alpha_csv << std::format("{:>15},{:>15}", "Альфа", "Время") << "\n";

    double t = 0.0;
    for(const auto& point: Points)
    {
        // std::println("{},{}", point.H, point.V);
        alpha_csv << std::format("{:>15.5},{:>15.5}", point.alpha*180.0/M_PI, t ) << "\n";
        alpha_csv << std::format("{:>15.5},{:>15.5}", point.alpha*180.0/M_PI, t += point.time_spent) << "\n";
    }
    //cat trajectory.csv в терминале чтобы проверить вывод
    alpha_csv.close();
}
void Trajectory::Delete()
{
    Points.clear();
    Alphas.clear();
}
void Trajectory::GenerateGPLOTScript(const std::string& file_prefix, const std::string& hvcsv, const std::string& acsv)
{
    std::ofstream ofile(file_prefix+std::string("plothv.gp"), std::ios::out);
    if(!ofile.is_open())
    {
        std::println("Не удалось сгенерировать скрипт");
        return;
    }

    // ofile << "set terminal wxt size 1200,800 font 'Arial,12'\n";
    
    ofile << "set terminal wxt size 800,600\n";
    ofile << "set output 'trajectory.png'\n";

    ofile << "set title 'Траектория полета'\n";
    ofile << "set xlabel 'Скорость, км/ч'\n";
    ofile << "set ylabel 'Высота, м'\n";

    // ofile << std::format("set xtics ('Старт' {}, 'Конец' {})\n", Points.begin()->v, Points.end()->v);
    // for(const auto& point: Points)
    // {
    //
    // }
    // ofile << "set xtics (400, 500, 600, 800)\n";
    ofile << "set grid\n";
    ofile << "plot '" << hvcsv << "' using 2:1 with linespoints title 'Траектория полета'";
    ofile << "\n";

    ofile.close();

    std::ofstream ofile2(file_prefix+std::string("plotalpha.gp"), std::ios::out);
    if(!ofile2.is_open())
    {
        std::println("Не удалось сгенерировать скрипт");
        return;
    }
    ofile2 << "set terminal wxt size 800,600\n";
    ofile2 << "set output 'alpha.png'\n";

    ofile2 << "set title 'Траектория полета'\n";
    ofile2 << "set xlabel 'Время, с'\n";
    ofile2 << "set ylabel 'Alpha, градусы'\n";

    // ofile << std::format("set xtics ('Старт' {}, 'Конец' {})\n", Points.begin()->v, Points.end()->v);
    // for(const auto& point: Points)
    // {
    //
    // }
    // ofile << "set xtics (400, 500, 600, 800)\n";
    ofile2 << "set grid\n";
    ofile2 << "plot '" << acsv << "' using 2:1 with linespoints title 'Траектория полета'";
    ofile2 << "\n";

    ofile2.close();
    
}
