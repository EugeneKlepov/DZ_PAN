#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	double m, L, D, T;
	double g = 9.8;
	cout << "Введите массу самолёта m" << endl;
	cin >> m;
	cout << "Введите подъёмнную силу L" << endl;
	cin >> L;
	cout << "Введите сопротивление D" << endl;
	cin >> D;
	cout << "Введите тягу двигателя T" << endl;
	cin >> T;
	double a = (T - D) / m;
	cout << "ускорение = " << a << endl;
	double ay = (L - m * g) / m;
	cout << "вертикальное ускорение = " << ay << endl;
	return 0;
}

