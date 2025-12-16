#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	int plane1[8];
	int plane2[8];
	int plane3[8];
	int z = 0;
	int x = 0;
	int c = 0;
	float g = 9.8;
	int t = 0;
	cout << "Введите время t";
	cin >> t;
	cout << "Введите массу m,площадь крыла S,тягу T,плотность воздуха p,объёмом V, сопротивлением D и коэффициентом сопротивления СD  для 1-ого самолёта" << endl;
	for (int i = 0; i < 7; i++) {
		cin >> z;
		plane1[i] = z;
	}
	cout << "Введите массу m,площадь крыла S,тягу T,плотность воздуха p,объёмом V, сопротивлением D и коэффициентом сопротивления СD  для 2-ого самолёта" << endl;
	for (int i = 0; i < 7; i++) {
		cin >> x;
		plane2[i] = x;
	}
	cout << "Введите массу m,площадь крыла S,тягу T,плотность воздуха p,объёмом V, сопротивлением D и коэффициентом сопротивления СD  для 3-ого самолёта" << endl;
	for (int i = 0; i < 7; i++) {
		cin >> z;
		plane3[i] = c;
	}
	double L1 = 0.5 * plane1[3] * plane1[4] * plane1[4] * plane1[1] * plane1[1];
	double L2 = 0.5 * plane2[3] * plane2[4] * plane2[4] * plane2[1] * plane2[1];
	double L3 = 0.5 * plane3[3] * plane3[4] * plane3[4] * plane3[1] * plane3[1];
	double a1 = (plane1[2] - plane1[5]) / plane1[0];
	double ay1 = (L1 - plane1[0] * g) / plane1[0];
	double a2 = (plane2[2] - plane2[5]) / plane2[0];
	double ay2 = (L2 - plane2[0] * g) / plane2[0];
	double a3 = (plane3[2] - plane3[5]) / plane3[0];
	double ay3 = (L3 - plane3[0] * g) / plane3[0];
	double h1 = 0.5 * ay1 * t * t;
	double h2 = 0.5 * ay2 * t * t;
	double h3 = 0.5 * ay3 * t * t;
	if ((h1 > h2) and (h1 > h3)) {
		cout << "Быстрее всех наберёт высоту 1-ый самолёт, его h=" << h1 << endl << "его а=" << a1 << endl;
		if (h2 > h3) {
			cout<<"Вторым наберёт высоту 2-ой самолёт, его h=" << h2 << endl << "его а=" << a2 << endl;
			cout << "Третьим наберёт высоту 3-ой самолёт, его h=" << h3 << endl << "его а=" << a3 << endl;
		}
		else {
			cout << "Вторым наберёт высоту 3-ий самолёт, его h=" << h3 << endl << "его а=" << a3 << endl;
			cout << "Третьим наберёт высоту 2-ой самолёт, его h=" << h2 << endl << "его а=" << a2 << endl;
		}
	}
	if ((h2 > h1) and (h2 > h3)) {
		cout << "Быстрее всех наберёт высоту 2-ой самолёт, его h=" << h2 << endl << "его а=" << a2 << endl;
		if (h1 > h3) {
			cout << "Вторым наберёт высоту 1-ый самолёт, его h=" << h1 << endl << "его а=" << a1 << endl;
			cout << "Третьим наберёт высоту 3-ий самолёт, его h=" << h3 << endl << "его а=" << a3 << endl;
		}
		else {
			cout << "Вторым наберёт высоту 3-ий самолёт, его h=" << h3 << endl << "его а=" << a3 << endl;
			cout << "Третьим наберёт высоту 1-ый самолёт, его h=" << h1 << endl << "его а=" << a1 << endl;
		}
	}
	if ((h3 > h1) and (h1 > h2)) {
		cout << "Быстрее всех наберёт высоту 3-ий самолёт, его h=" << h3 << endl << "его а=" << a3 << endl;
		if (h1 > h2) {
			cout << "Вторым наберёт высоту 1-ый самолёт, его h=" << h1 << endl << "его а=" << a1 << endl;
			cout << "Третьим наберёт высоту 2-ой самолёт, его h=" << h2 << endl << "его а=" << a2 << endl;
		}
		else {
			cout << "Вторым наберёт высоту 2-ой самолёт, его h=" << h2 << endl << "его а=" << a2 << endl;
			cout << "Третьим наберёт высоту 1-ый самолёт, его h=" << h1 << endl << "его а=" << a1 << endl;
		}
	}





	return 0;
}
