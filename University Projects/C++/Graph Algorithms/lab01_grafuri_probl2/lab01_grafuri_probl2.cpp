#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("graf.txt");

int main()
{
	int adj[100][100];
	int nr, x, y;
	fin >> nr;
	for (int i = 1; i <= nr; i++)
		for (int j = 1; j <= nr; j++)
			adj[i][j] = 0;
	while (fin >> x >> y) {
		adj[x][y] = 1;
		adj[y][x] = 1;
	}
	
	cout << "Matricea de adiacenta:\n";
	for (int i = 1; i <= nr; i++) {
		for (int j = 1; j <= nr; j++)
			cout << adj[i][j] << " ";
		cout << "\n";
	}
	
	cout << "Nodurile izolate:\n";
	int vecini[100];
	for (int i = 1; i <= nr; i++) {
		vecini[i] = 0;
		for (int j = 1; j <= nr; j++) {
			if (adj[i][j] == 1) 
				vecini[i]++;
		}
		if (!vecini[i])
			cout << i << " ";
	}
	cout << "\n";

	cout << "Graf regulat: ";
	int ok = 1;
	int grad = vecini[1];
	for (int i = 1; i <= nr; i++)
		if (vecini[i] != grad) {
			ok = 0;
			break;
		}
	if (ok) cout << "DA\n";
	else cout << "NU\n";
	
	int dist[100][100], inf = 100000;
	for (int i = 1; i <= nr; i++)
		for (int j = 1; j <= nr; j++) {
			if (adj[i][j] == 1) dist[i][j] = 1;
			else if (i == j) dist[i][j] = 0;
			else dist[i][j] = inf;
		}
	for (int k = 1; k <= nr; ++k)
		for (int i = 1; i <= nr; ++i)
			for (int j = 1; j <= nr; ++j)
				if (dist[i][j] > dist[i][k] + dist[k][j])
					dist[i][j] = dist[i][k] + dist[k][j];
	cout << "Matricea distantelor:\n";
	for (int i = 1; i <= nr; i++) {
		for (int j = 1; j <= nr; j++)
			cout << dist[i][j] << " ";
		cout << "\n";
	}

	cout << "Graf conex: ";
	ok = 1;
	for (int i = 1; i <= nr; i++)
		for (int j = 1; j <= nr; j++)
			if (dist[i][j] == inf)
				ok = 0;
	if (ok) cout << "DA\n";
	else cout << "NU\n";

	fin.close();
	return 0;
}