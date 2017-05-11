#include<iostream>
#include<vector>
#include<list>
#include<cstdlib>
#include<ctime>
#include<Windows.h>

using namespace std;

int main() {

	int start, end; //pkt startowy i koncowy
	int n = 100; //liczba wierzcholkow grafu
	bool test = true;
	start = 0;
	end = n - 1;

	long double ms;
	unsigned __int64 freq, counterStart, counterStop;

	vector<vector<int>> grapf(n, vector<int>(n)); //tablica wag grawedzi (graf)
	vector<vector<bool>> pass(n, vector<bool>(n));//tablica mozliwych przejsc 0-mozliwe 1 nie 

	vector<vector<bool>> pass_backup(n, vector<bool>(n));//tablica zapasowa do mozliwych przejsc

	vector<vector<int>>tab_u_v(2, vector<int>(n));//tabilca w ktorej bedziemy zapisywac wage przejsc[0][n] a takze poprzedni wierzcholek[1][n]

	//inicjalizujemy poszczegolne tablice

	srand(time(NULL));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				grapf[i][j] = 101;
				pass[i][j] = 1;
				pass_backup[i][j] = 1;
			}
			else {
				grapf[i][j] = ((rand() % 50) + 1);
				pass[i][j] = 0;
				pass_backup[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		tab_u_v[0][i] = 101;
		tab_u_v[1][i] = -1;
	}

	//bellman ford algorytm
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*> (&freq));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*> (&counterStart));
	tab_u_v[0][start] = 0;

	for (int i = 1; i < n; i++)//petla iteracji do algorytmu bellmana-forda (glowna petla musi mimec n-1 iteracji
	{
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (pass[i][j] == 0) {
					if((tab_u_v[0][i] + grapf[i][j]) < tab_u_v[0][j]){
						tab_u_v[0][j] = tab_u_v[0][i] + grapf[i][j];
						tab_u_v[1][j] = i;}} 
						}}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (pass[i][j] == 0) {
				if ((tab_u_v[0][i] + grapf[i][j]) < tab_u_v[0][j]) {
					tab_u_v[0][j] = tab_u_v[0][i] + grapf[i][j];
					tab_u_v[1][j] = i;
				}
			}
		}
	}
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*> (&counterStop));


	//pass_backup.swap(pass);//podemieni tablica zapasowa do glownej

	//wyswietlenia
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << pass[i][j] << " ";
		cout << endl;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << grapf[i][j] << " ";
		cout << endl;
	}
	*/
	list<int> notvisited;
	int trackingid;
	int a = n - 1;
	//for (int i = 0; i < n; a++)
	//{
		trackingid = a;

		while (trackingid != -1) {
			notvisited.push_front(trackingid);
			trackingid = tab_u_v[1][trackingid];
		}

		cout << "koszty przejscia sciezki " << a << ": " << endl;

		for (list<int>::iterator i = notvisited.begin(); i != notvisited.end(); ++i)
			cout << *i << "->";
		cout << "koszt przejscia :" << tab_u_v[0][a] << endl;
		notvisited.clear();
	//}

			ms = (static_cast<long double> (counterStop) - counterStart) / freq * 1000;
		cout << endl << endl << ms << endl;

	system("pause");
}