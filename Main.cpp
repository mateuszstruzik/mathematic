#include<iostream>
#include<vector>
#include<list>
#include<cstdlib>
#include<ctime>

using namespace std;

int main() {

	int start, end; //pkt startowy i koncowy
	int n = 5; //liczba wierzcholkow grafu
	bool test = true;
	start = 0;
	end = n - 1;
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
		tab_u_v[0][n] = 101;
		tab_u_v[1][n] = -1;
	}

	//bellman ford algorytm
	tab_u_v[0][start] = 0;
	
	for (int i = 1; i < n; i++)//petla iteracji do algorytmu bellmana-forda (glowna petla musi mimec n-1 iteracji
	{

	}
	//pass_backup.swap(pass);//podemieni tablica zapasowa do glownej

	//wyswietlenia
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << pass[i][j] << " ";
		cout << endl;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << grapf[i][j] << " ";
		cout << endl;
	}

	system("pause");
}