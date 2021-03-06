// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "pch.h"

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <fstream>
using namespace std;


double gen(double &x) {
	std::default_random_engine generator;
	std::gamma_distribution<double> distribution(3.71, 1.0);
	double y;
	try {
		y = distribution(generator);
		if (y > 15)
			throw 'e';
		x = y;
	}
	catch (char c) {
		cout << "wieksza od 18" << endl;
	}
	return x;
}

void wypisz(double x) {
	cout << fixed << setprecision(6) << x << endl;
}

int main()
{
	std::default_random_engine generator;
	std::gamma_distribution<double> distribution(3.71, 1.0);
	vector<double> A(100000);
	vector<int> B(180);
	vector<double> C(180);
	vector<double> D(180);
	//for_each(B.begin(), B.end(), [](int &x){ x = 0; });
	vector<double>::iterator it = A.begin();

	for (int& i : B) {
		i = 0;
	}

	for (; it != A.end(); it++) {
		try {
			double y = distribution(generator);
			if (y > 18)
				throw 'c';
			*it = y;
		}
		catch (char) {
			it--;
		}
	}
	//for_each(A.begin(), A.end(), wypisz);
	for_each(A.begin(), A.end(), [&B](double x) {B[(int)(x * 10)]++; }); //zlicza wystąpienia w przedziałach
	cout << endl;
	//for_each(B.begin(), B.end(), wypisz);
	int suma = accumulate(B.begin(), B.end(), 0);
	cout << endl << "suma=" << suma << endl << endl;
	int i = 0;
	for_each(C.begin(), C.end(), [&](double &x) {x = (double)B[i] / (double)suma; i++; });
	//cout << endl<<accumulate(C.begin(), C.end(), 0.0);
	//for_each(C.begin(), C.end(), wypisz);
	partial_sum(C.begin(), C.end(), D.begin());
	//for_each(C.begin(), C.end(), wypisz);
	//cout << "///////////////////////////////" << endl;
	//for_each(D.begin(), D.end(), wypisz);
	double j = 0;
	fstream plik("plik.txt", ios::out), plik2("plik2.txt", ios::out);
	for_each(C.begin(), C.end(), [&j, &plik](double x) {plik << (j + 1) / 10 << '\t' << x << endl; j++; });
	j = 0;
	for_each(D.begin(), D.end(), [&](double x) {plik2 << (j + 1) / 10 << '\t' << x << endl; j++; });
	system("pause");
	return 0;

}

