#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("graf.txt");

int main()
{
    int vf, adj[10][10];

    fin >> vf;

    vector<pair<int, int>> muchii;

    for (int i = 1; i <= vf; i++) {
        for (int j = 1; j <= vf; j++) {
            fin >> adj[i][j];
            if(adj[i][j])
                muchii.push_back(make_pair(i,j));
        }
    }

    for (int i = 0; i < muchii.size(); i++) {
        cout << muchii[i].first << ' ' << muchii[i].second << '\n';
    }

    fin.close();
    return 0;
}