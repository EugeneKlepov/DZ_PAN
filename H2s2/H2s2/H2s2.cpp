#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	double S, V, p, CD, FD, A,q;
	cout << "Введите площадь крыла S" << endl;
	cin >> S;
	cout << "Введите скоростью полета V" << endl;
	cin >> V;
	cout << "Введите плотность воздуха p" << endl;
	cin >> p;
	cout <<"Введите силу  сопротивления FD" << endl;
	cin >> FD;
	cout << "Введите область потока А" << endl;
	cin >> A;
	cout << "Введите диеамическое давление q" << endl;
	cin >> q;
	CD = FD / q / A;
	double L = 0.5 * p * V * V * S * CD;
	cout << "подъемная сила равна - ";
	cout << L;

	return 0;
}
