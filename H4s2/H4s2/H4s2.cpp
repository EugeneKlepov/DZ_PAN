#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	double m, L, h;
	double g = 9.8;
	cout << "Введите массу самолёта m" << endl;
	cin >> m;
	cout << "Введите подъёмнную силу L" << endl;
	cin >> L;
	cout << "Введите высоту h" << endl;
	cin >> h;
	double ay = (L - m * g) / m;
	double t = sqrt(2 * h / ay);
	if (m > 0){
		if (ay > 0 and m < 0) {
			cout << "t = " << t << endl;
		}
		else {
			cout << "Ускорение отрицательное, переделывай" << endl;
		}
	}else{
		cout << "Масса отрицательная, переделывай"<<endl;
	}
	return 0;
}
	

