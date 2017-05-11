#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<Windows.h>

using namespace std;

int main() {

	srand(time(NULL));
	int n = 1000;
	int start = 2;
	int end = n - 1;

	time_t str, koniec;
	long double ms;
	unsigned __int64 freq, counterStart, counterStop;
	vector<vector<int>> graph(n, vector<int>(n));
	

	//losowanie grafu przejsc
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				graph[i][j] = 101;
			else
				graph[i][j] = ((rand() % 50) + 1);
		}
	}
	//graph bez powtorzen
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			graph[j][i] = graph[i][j];
	}
	//wypisanie graphu
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++)
	//		cout << graph[i][j]<<" ";
	//	cout << endl;
	//}

	vector<vector<int>> pass(n, vector<int>(n));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				pass[i][j] = 1;
			else
				pass[i][j] = 0;
		}
	}

	vector<vector<int>> peak(2, vector<int>(n));

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == 0)
				peak[i][j]=101;
			else
			{
				peak[i][j] = -1;
			}
		}
			
	}

	peak[0][start] = 0;
	peak[1][start] = -1;

	list<int> notvisited;

	for (int i = 0; i < n ; i++)
		notvisited.push_back(i);

	int compare = 101; //bedzie sluzyc do porownania wartosci w tablicy peak
	int trackingid = n + 1; //bedzie sluzyc do zapisania w tablicy peak ostatniego odwiedzonego wierzcholka

	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*> (&freq));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*> (&counterStart));
	
	//step 1 : znalezienie najmniejszej wartosci w tablicy peak
while(!notvisited.empty()){
	for (int i = 0; i<n; i++) {
		//porownujemy czy dana wartosc jest njmniejsza w tablicy w wierszu wartosci peak[0][n], a takze czy dany wierzcholek nie byl juz brany pod uwage, czy jest w liscie(zbiorze) wierzcholkow nie odwiedzonych
		if (peak[0][i] < compare && (find(notvisited.begin(), notvisited.end(), i) != notvisited.end())) {
			compare = peak[0][i];
			trackingid = i;

		}

	}
	//usuniecie z listy elementu o najmniejszej wartosci w tablicy [2][n]
	notvisited.remove(trackingid);
	//sprawdzenie czy z wierzcholka jest przejscie do innych a takze czy nie byl juz wczesniej odwiedzony
	for (int i = 0; i<n; i++) {
		if (graph[trackingid][i]<101 && pass[trackingid][i] == 0) {
			//porownanie czy wartosc przypisana do wierzcholkow po ostatnim przejsciu jest wieksza od tej przy tym przejsciu
			if (peak[0][i] > (compare + graph[trackingid][i])) {
				peak[0][i] = compare + graph[trackingid][i]; //jesli poprzednia wartosc w wierszu tablicy [0][n] byla iweksza zamienienie nan nowa
				peak[1][i] = trackingid; //podmiana ostatnio odwiedzonego wierzcholka
				pass[trackingid][i] = 1;  //zapisanie w tablicy przejsc odwiedzonych wierzcholkow bez powtorzen
				pass[i][trackingid] = 1;
			}
		}
	}
	compare = 101;
}
QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*> (&counterStop));



	//-----wyswitlenia----
	/*cout << "lista " << endl;
	for (list<int>::iterator i = notvisited.begin(); i != notvisited.end(); ++i)
		cout << *i;
	cout << endl;
	
	cout << "wysietla przejscia"<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << pass[i][j];
		}
		cout << endl;
	}

	cout << "wyswietla tablcie zaleznosci" << endl;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << peak[i][j]<<"  ";
		}
		cout << endl;
	}

	//backtracking
	*/
	//for (int i = 0; i < n; i++)
	//{
trackingid = n - 1;//i;

		while (trackingid != -1) {
			notvisited.push_front(trackingid);
			trackingid = peak[1][trackingid];
		}
	
		cout << "koszty przejscia sciezki " << n-1 << ": " << endl;

		for (list<int>::iterator i = notvisited.begin(); i != notvisited.end(); ++i)
			cout << *i << "->";
		cout << "koszt przejscia :"<<peak[0][n-1]<<endl;
		notvisited.clear();
	//}
		ms = (static_cast<long double> (counterStop) - counterStart) / freq * 1000;
	cout << endl << endl << ms<<endl;


	system("pause");

}