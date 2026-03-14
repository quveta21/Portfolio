#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

ifstream fin("graf.txt");
ofstream fout("graf.out");

int matr_adj[100][100], matr_inc[100][100];
vector <list <int>> neighbours(100);

int main()
{
	int nr, x, y, e = 1;
	fin >> nr;

	while (fin >> x >> y) {
		matr_adj[x][y] = 1;
		matr_adj[y][x] = 1;

		matr_inc[x][e] = 1;
		matr_inc[y][e] = 1;
		e++;

		neighbours[x].push_back(y);
		neighbours[y].push_back(x);
	}

	fout << "Matricea de adiacenta:\n";
	for (int i = 1; i <= nr; i++) {
		for (int j = 1; j <= nr; j++)
			fout << matr_adj[i][j] << " ";
		fout << "\n";
	}

	fout << "Matricea de incidenta:\n";
	for (int i = 1; i <= nr; i++) {
		for (int j = 1; j <= nr; j++)
			fout << matr_inc[i][j] << " ";
		fout << "\n";
	}

	fout << "Lista de adiacenta:\n";
	for (int i = 1; i <= nr; ++i) {
		fout << i << ": ";
		for (int neighbour : neighbours[i]) {
			fout << neighbour << " ";
		}
		fout << "\n";
	}

	fin.close();
	fout.close();
	return 0;
}
