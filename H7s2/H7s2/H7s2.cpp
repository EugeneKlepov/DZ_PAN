
#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	cout << "Введите a"<<endl;
	double a;
	cin >> a;
	
		if (a > 0.5) {
			cout << "установлен режим <Набор высоты>";
		}
		else if (a <= 0.5 and a >= 0) {
			cout << "установлен режим <Горизонтальный полёт>";
		}
		else {
			cout << "установлен режим <Снижение>";
		}
	}

