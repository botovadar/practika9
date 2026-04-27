//Вариант 4.
//Определить структурный тип, описывающий расписание полетов самолетов(пункт
//	посадки, время отправления, время прибытия, время полета, стоимость билета, тип
//	рейса : чартер, транзит, стыковка).Заполнить структурный массив 20 - ю записями.
//	Переписать из исходного массива в другой массив, информацию только о тех рейсах
//	пункт назначения, которых оканчивается сочетанием «град» и рейс транзитный.
//	Затем новый массив отсортировать по времени полета(рационально переставлять
//	все поля структуры разом).Вывести все данные по конкретному рейсу.Вывести 5
//	чартерных рейсов, которые вылетают ночью.Реализовать функцию изменения
//	рейса.В отдельный массив поместить все стыковочные рейсы, стоимостью менее N
//	рублей.Реализовать вывод отфильтрованных данных в виде оберточной функции.

#include <iostream>
#include <cstring>
using namespace std;

const int SIZE = 20;
enum flight {ch, tr, st};
char flight_name[3][15] = { "charter", "transit", "stick" };
struct date {
	int d, m, y;
};
struct time1 {
	int h, min;
};
struct raspisanie {
	char point[20];
	date day;
	time1 otpr;
	time1 prib;
	int price;
	flight tip;
};

raspisanie* init() {
	raspisanie* rasp = new raspisanie[SIZE];
	rasp[0] = { "Tokyo", {2,12,2025}, {12,28}, { 16,23 }, 5000, st };
	rasp[1] = { "Bejing", {12,3,2024}, {22,9}, {4,2}, 15000, tr };
	rasp[2] = { "London", {11,9,2026}, {11,23}, {9,7}, 20000, ch };
	rasp[3] = { "Dubai", {8,10,2026}, {22,22}, {3,7}, 7000, st };
	rasp[4] = { "Moscow", {2,22,2022}, {23,1}, {5,6}, 35000, ch };
	rasp[5] = { "Rome", {2,12,2025}, {12,28}, { 17,26 }, 5000, st };
	rasp[6] = { "Barcelona", {11,5,2026}, {17,22}, {3,00}, 19000, tr };
	rasp[7] = { "Istanbul", {11,9,2026}, {0,23}, {19,2}, 23200, ch };
	rasp[8] = { "Amsterdam", {7,11,2029}, {22,12}, {13,7}, 20700, st };
	rasp[9] = { "Sydney", {1,1,2022}, {0,11}, {12,6}, 31000, ch };
	rasp[10] = { "Zelenograd", {2,12,2025}, {12,28}, { 20,26 }, 51000, tr };
	rasp[11] = { "Yekaterinburg", {11,5,2024}, {22,9}, {3,59}, 16000, tr };
	rasp[12] = { "Saint Petersburg", {11,9,2026}, {15,23}, {19,2}, 11300, ch };
	rasp[13] = { "Paris", {7,10,2021}, {12,22}, {13,7}, 20500, st };
	rasp[14] = { "Mexico", {1,1,2022}, {5,12}, {12,6}, 31000, ch };
	rasp[15] = { "Miass", {2,12,2025}, {12,28}, { 17,26 }, 5000, st };
	rasp[16] = { "Chelyabinsk", {11,5,2024}, {22,9}, {3,59}, 11000, tr };
	rasp[17] = { "Kaliningrad", {11,9,2026}, {15,23}, {19,2}, 2300, tr };
	rasp[18] = { "Volgograd", {7,10,2021}, {12,22}, {13,7}, 26000, st };
	rasp[19] = { "Belgrad", {1,1,2022}, {0,1}, {12,6}, 39000, tr };
	return rasp;
}

int flighttime(const raspisanie& fl) {
	int otprav = fl.otpr.h * 60 + fl.otpr.min;
	int pribit = fl.prib.h * 60 + fl.prib.min;
	if (pribit < otprav) {
		pribit += 24 * 60;
	}
	return pribit - otprav;
}

int citygrad(raspisanie* sched, int size, raspisanie* filt) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		int len = strlen(sched[i].point);
		if (len >= 4 && strcmp(&sched[i].point[len - 4], "grad") == 0 && sched[i].tip == tr) {
			filt[count] = sched[i];
			count++;
		}
	}
	return count;
}

void showgrad(raspisanie* flights, int count) {
	for (int i = 0; i < count; i++) {
		cout << flights[i].point << ": "
			<< flights[i].day.d << "." << flights[i].day.m << "." << flights[i].day.y << endl;
	}
}

void sortflights(raspisanie* flights, int count) {
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			int time1 = flighttime(flights[j]);
			int time2 = flighttime(flights[j + 1]);
			if (time1 > time2) {
				raspisanie temp = flights[j];
				flights[j] = flights[j + 1];
				flights[j + 1] = temp;
			}
		}
	}
}

void showsort(raspisanie* flights, int count) {
	for (int i = 0; i < count; i++) {
		cout << flights[i].point << ": " << flights[i].day.d << "." << flights[i].day.m << "." << flights[i].day.y << "; time = " << flighttime(flights[i]) << " min" << endl;
	}
}
void showinfocity(raspisanie& flight) {
	cout << "City: " << flight.point << endl;
	cout << "Date: " << flight.day.d << "." << flight.day.m << "." << flight.day.y << endl;
	cout << "Otpr: " << flight.otpr.h << ":" << flight.otpr.min << endl;
	cout << "Pribit: " << flight.prib.h << ":" << flight.prib.min << endl;
	cout << "Price: " << flight.price << " rub" << endl;
	cout << "Flight: " << flight_name[flight.tip] << endl;
}

void shownight(raspisanie* sched, int size) {
	cout << "Charter flights otpr at night:" << endl;
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (sched[i].otpr.h < 6 && sched[i].tip == ch && count < 5) {
			cout << sched[i].point << ": " << sched[i].otpr.h << ":" << sched[i].otpr.min << endl;
			count++;
		}
	}
	if (count == 0) {
		cout << "No flights found" << endl;
	}
}

void editflight(raspisanie& fl) {
	cout << "Enter new city (was: " << fl.point << "): ";
	cin.getline(fl.point, 20);
	cout << "Enter new date (day month year) (was: " << fl.day.d << "." << fl.day.m << "." << fl.day.y << "): ";
	cin >> fl.day.d >> fl.day.m >> fl.day.y;
	cout << "Enter new otpr time (hours minutes) (was: " << fl.otpr.h << ":" << fl.otpr.min << "): ";
	cin >> fl.otpr.h >> fl.otpr.min;
	cout << "Enter new prib time (hours minutes) (was: " << fl.prib.h << ":" << fl.prib.min << "): ";
	cin >> fl.prib.h >> fl.prib.min;
	cout << "Enter new price (was: " << fl.price << "): ";
	cin >> fl.price;
	int tip_choice;
	cout << "Enter new tip (0-charter, 1-transit, 2-stick) (was: " << flight_name[fl.tip] << "): ";
	cin >> tip_choice;
	if (tip_choice >= 0 && tip_choice <= 2) {
		fl.tip = (flight)tip_choice;
	}
}

int filtertrans(raspisanie* sched, int size, raspisanie* result, int N) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (sched[i].tip == tr && sched[i].price < N) {
			result[count] = sched[i];
			count++;
		}
	}
	return count;
}

void showfiltfl(raspisanie* flights, int count, int N) {
	if (count == 0) {
		cout << "No flights found" << endl;
		return;
	}
	for (int i = 0; i < count; i++) {
		cout << flights[i].point << ": " << flights[i].day.d << "." << flights[i].day.m << "." << flights[i].day.y << " Price: " << flights[i].price << " rub" << endl;
	}
}

int main() {
	raspisanie* sched = init();
	cout << "Vse flights" << endl << endl;

	for (int i = 0; i < SIZE; i++) {
		cout << sched[i].point << ": " << sched[i].day.d << "." << sched[i].day.m << "." << sched[i].day.y << endl;
	}

	raspisanie filt2[SIZE];
	int count = 0;
	cout << endl;
	cout << "Na 'grad' and tr" << endl << endl;
	count = citygrad(sched, SIZE, filt2);

	showgrad(filt2, count);

	sortflights(filt2, count);

	cout << endl;
	cout << "Sortirovka po time flight" << endl << endl;
	showsort(filt2, count);

	cout << endl;
	shownight(sched, SIZE);
	showinfocity(sched[3]);

	cout << endl;
	cout << "Before edit: " << endl;
	cout << endl;
	showinfocity(sched[14]);
	cout << endl;
	editflight(sched[14]);
	cout << "After edit: " << endl;
	cout << endl;
	showinfocity(sched[14]);
	cout << endl;

	int N;
	cout << "Enter max price of flight: " << endl;
	cin >> N;
	raspisanie transfl[SIZE];
	int transcount = filtertrans(sched, SIZE, transfl, N);
	cout << endl;
	showfiltfl(transfl, transcount, N);

	delete[] sched;
	return 0;
}
