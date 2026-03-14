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
		adj[x][x] = 1;
	}

	cout << "Graful initial:\n";
	for (int i = 1; i <= nr; i++) {
		for (int j = 1; j <= nr; j++)
			cout << adj[i][j] << " ";
		cout << "\n";
	}

	for (int k = 1; k <= nr; k++)
		for (int i = 1; i <= nr; i++)
			for (int j = 1; j <= nr; j++)
				if (adj[i][j] == 0)
					if (adj[i][k] && adj[k][j])
						adj[i][j] = 1;

	cout << "Inchiderea tranzitiva:\n";
	for (int i = 1; i <= nr; i++) {
		for (int j = 1; j <= nr; j++)
			cout << adj[i][j] << " ";
		cout << "\n";
	}

	fin.close();
	return 0;
}
