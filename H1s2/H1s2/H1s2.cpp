#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	double S, V, p, CL;
	cout << "Введите площадь крыла S" << endl;
	cin >> S;
	cout << "Введите скоростью полета V" << endl;
	cin >> V;
	cout << "Введите плотность воздуха p" << endl;
	cin >> p;
	cout << "Введите коэффициентом подъемной силы CL" << endl;
	cin >> CL;
	double L = 0.5 * p * V * V * S * CL;
	cout << "подъемная сила равна - ";
	cout << L;

	return 0;
}

