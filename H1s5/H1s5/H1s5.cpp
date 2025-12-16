#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

// ==================== КЛАСС AIRCRAFT ====================
class Aircraft {
public:
    double mass;      // масса (кг)
    double P;         // тяга двигателя (Н)
    double Cp;        // удельный расход топлива (кг/Н·с)
    double Cx, Cy;    // коэффициенты аэродинамики (Cx - лобовое сопротивление, Cy - подъемная сила)
    double x, y;      // координаты (м)
    double V;         // скорость (м/с)
    double fuel;      // остаток топлива (кг)
    double theta;     // угол наклона траектории (рад)
    double alpha;     // угол атаки (рад)

    Aircraft(double m, double thrust, double cp, double cx, double cy, double initialFuel)
        : mass(m), P(thrust), Cp(cp), Cx(cx), Cy(cy), fuel(initialFuel) {
        x = 0.0;
        y = 0.0;
        V = 0.0;
        theta = 0.0;
        alpha = 0.05; // небольшой начальный угол атаки
    }

    // Вычисление сил
    void computeForces(double rho, double& lift, double& drag) const {
        double q = 0.5 * rho * V * V; // динамическое давление
        lift = q * Cy;
        drag = q * Cx;
    }

    // Обновление состояния за шаг dt
    void updateState(double dt, double rho) {
        double lift, drag;
        computeForces(rho, lift, drag);

        // Ускорения
        double ax = (P * cos(theta + alpha) - drag * cos(theta) - mass * 9.81 * sin(theta)) / mass;
        double ay = (lift + P * sin(theta + alpha) - mass * 9.81 * cos(theta)) / mass;

        // Обновление скорости и координат
        V += ax * dt;
        x += V * cos(theta) * dt;
        y += V * sin(theta) * dt;

        // Обновление угла наклона (упрощенно)
        theta = atan2(V * sin(theta) + ay * dt, V * cos(theta) + ax * dt);

        // Расход топлива
        double fuelUsed = Cp * P * dt;
        fuel -= fuelUsed;
        if (fuel < 0) fuel = 0;
    }

    void printStatus() const {
        std::cout << "x=" << x << " м, y=" << y << " м, V=" << V << " м/с, топливо=" << fuel << " кг, theta=" << theta * 180 / 3.14159 << "°\n";
    }

    virtual ~Aircraft() {}
};

// ==================== КЛАСС ENVIRONMENT ====================
class Environment {
public:
    double rho0;    // плотность на уровне моря (кг/м³)
    double T0;      // температура на уровне моря (К)
    double P0;      // давление на уровне моря (Па)

    Environment(double rho = 1.225, double T = 288.15, double P = 101325)
        : rho0(rho), T0(T), P0(P) {
    }

    // Плотность на высоте H (упрощенная модель)
    double getDensity(double H) const {
        // Экспоненциальная модель атмосферы
        return rho0 * exp(-H / 8500.0);
    }

    // Давление на высоте H
    double getPressure(double H) const {
        return P0 * exp(-H / 8500.0);
    }
};

// ==================== КЛАСС TRAJECTORYPOINT ====================
struct TrajectoryPoint {
    double x, y;     // координаты
    double V;        // скорость
    double fuel;     // расход топлива до этой точки
    double time;     // время от старта
    double theta;    // угол наклона

    TrajectoryPoint(double xx = 0, double yy = 0, double vv = 0,
        double ff = 0, double tt = 0, double th = 0)
        : x(xx), y(yy), V(vv), fuel(ff), time(tt), theta(th) {
    }

    void print() const {
        std::cout << "t=" << time << " с, x=" << x << " м, y=" << y << " м, V=" << V << " м/с, топливо=" << fuel << " кг\n";
    }
};

// ==================== КЛАСС TRAJECTORY ====================
class Trajectory {
private:
    std::vector<TrajectoryPoint> points;
public:
    Trajectory() {}

    void addPoint(const TrajectoryPoint& p) {
        points.push_back(p);
    }

    const std::vector<TrajectoryPoint>& getPoints() const {
        return points;
    }

    void print() const {
        std::cout << "\n=== ТРАЕКТОРИЯ ===" << std::endl;
        for (const auto& p : points) {
            p.print();
        }
        std::cout << "Всего точек: " << points.size() << std::endl;
    }

    double getTotalTime() const {
        if (points.empty()) return 0;
        return points.back().time;
    }

    double getFuelUsed() const {
        if (points.empty()) return 0;
        return points.front().fuel - points.back().fuel;
    }
};

// ==================== КЛАСС DYNAMICPROGRAMMINGSOLVER ====================
class DynamicProgrammingSolver {
private:
    std::vector<std::vector<double>> costGrid; // сетка стоимостей
    std::vector<std::vector<TrajectoryPoint>> pointGrid; // сетка точек
    std::vector<std::vector<int>> prevI, prevJ; // для восстановления пути
    std::string criterion; // "minFuel" или "minTime"

public:
    DynamicProgrammingSolver(const std::string& crit = "minFuel") : criterion(crit) {}

    // Основной метод расчета оптимальной траектории
    Trajectory computeOptimalTrajectory(Aircraft& ac, Environment& env,
        double H_max, double V_max,
        double H_step, double V_step,
        double dt, double totalTime) {
        int H_steps = static_cast<int>(H_max / H_step) + 1;
        int V_steps = static_cast<int>(V_max / V_step) + 1;

        // Инициализация сеток
        costGrid.assign(H_steps, std::vector<double>(V_steps, std::numeric_limits<double>::max()));
        pointGrid.assign(H_steps, std::vector<TrajectoryPoint>(V_steps));
        prevI.assign(H_steps, std::vector<int>(V_steps, -1));
        prevJ.assign(H_steps, std::vector<int>(V_steps, -1));

        // Начальное состояние (y=0, V=0)
        costGrid[0][0] = 0;
        pointGrid[0][0] = TrajectoryPoint(0, 0, 0, ac.fuel, 0, ac.theta);

        // Динамическое программирование
        for (int i = 0; i < H_steps; ++i) {
            for (int j = 0; j < V_steps; ++j) {
                if (costGrid[i][j] == std::numeric_limits<double>::max()) continue;

                double H = i * H_step;
                double V = j * V_step;

                // Возможные переходы
                for (int di = 0; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        int ni = i + di;
                        int nj = j + dj;

                        if (ni >= H_steps || nj >= V_steps || nj < 0) continue;

                        double newH = ni * H_step;
                        double newV = nj * V_step;

                        // Упрощенный расчет перехода
                        double dH = newH - H;
                        double dV = newV - V;
                        double distance = sqrt(dH * dH + dV * dV);
                        double timeStep = distance / (V + 0.1); // чтобы не делить на 0

                        // Расчет стоимости перехода
                        double fuelCost = ac.Cp * ac.P * timeStep;
                        double timeCost = timeStep;

                        double transitionCost = 0;
                        if (criterion == "minFuel") {
                            transitionCost = fuelCost;
                        }
                        else if (criterion == "minTime") {
                            transitionCost = timeCost;
                        }

                        double newCost = costGrid[i][j] + transitionCost;

                        if (newCost < costGrid[ni][nj]) {
                            costGrid[ni][nj] = newCost;
                            prevI[ni][nj] = i;
                            prevJ[ni][nj] = j;

                            // Сохраняем точку
                            double newX = pointGrid[i][j].x + V * cos(ac.theta) * timeStep;
                            double newY = newH;
                            double newFuel = pointGrid[i][j].fuel - fuelCost;
                            double newTime = pointGrid[i][j].time + timeStep;

                            pointGrid[ni][nj] = TrajectoryPoint(newX, newY, newV,
                                newFuel, newTime, ac.theta);
                        }
                    }
                }
            }
        }

        // Восстановление траектории
        return traceBack(H_steps - 1, V_steps - 1);
    }

private:
    Trajectory traceBack(int i, int j) {
        Trajectory traj;
        while (i >= 0 && j >= 0) {
            traj.addPoint(pointGrid[i][j]);
            int pi = prevI[i][j];
            int pj = prevJ[i][j];
            i = pi;
            j = pj;
            if (i == -1 || j == -1) break;
        }

        // Развернем траекторию в правильном порядке
        std::vector<TrajectoryPoint> points = traj.getPoints();
        std::reverse(points.begin(), points.end());
        Trajectory result;
        for (const auto& p : points) {
            result.addPoint(p);
        }
        return result;
    }
};

// ==================== MAIN ====================
int main() {
    std::cout << "=== МОДЕЛИРОВАНИЕ ПОЛЕТА САМОЛЕТА ===" << std::endl;

    // 1. Создание самолета
    Aircraft ac(20000.0,   // масса 20 тонн
        50000.0,   // тяга 50 кН
        0.0001,    // удельный расход топлива
        0.05,      // Cx
        0.8,       // Cy
        5000.0);   // начальный запас топлива

    // 2. Создание атмосферы
    Environment env;

    // 3. Решение методом динамического программирования
    DynamicProgrammingSolver solver("minFuel");

    double H_max = 10000.0;   // максимальная высота
    double V_max = 300.0;     // максимальная скорость
    double H_step = 500.0;    // шаг по высоте
    double V_step = 20.0;     // шаг по скорости
    double dt = 1.0;          // шаг времени
    double totalTime = 300.0; // общее время моделирования

    Trajectory optimalTraj = solver.computeOptimalTrajectory(ac, env,
        H_max, V_max,
        H_step, V_step,
        dt, totalTime);

    // 4. Вывод результатов
    optimalTraj.print();

    std::cout << "\n=== СВОДКА ===" << std::endl;
    std::cout << "Общее время полета: " << optimalTraj.getTotalTime() << " с" << std::endl;
    std::cout << "Израсходовано топлива: " << optimalTraj.getFuelUsed() << " кг" << std::endl;

    // 5. Простое пошаговое моделирование для сравнения
    std::cout << "\n=== ПРЯМОЕ МОДЕЛИРОВАНИЕ (10 шагов) ===" << std::endl;
    Aircraft ac2(20000.0, 50000.0, 0.0001, 0.05, 0.8, 5000.0);
    for (int step = 0; step < 10; ++step) {
        ac2.updateState(1.0, env.getDensity(ac2.y));
        std::cout << "Шаг " << step << ": ";
        ac2.printStatus();
        if (ac2.fuel <= 0) {
            std::cout << "Топливо закончилось!" << std::endl;
            break;
        }
    }

    return 0;
}