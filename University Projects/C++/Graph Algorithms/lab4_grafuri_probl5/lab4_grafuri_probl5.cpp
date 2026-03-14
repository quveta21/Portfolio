#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Muchie {
    int u, v, cost;

    Muchie(int u, int v, int cost) : u(u), v(v), cost(cost) {}

    bool operator<(const Muchie& other) const {
        return cost < other.cost;
    }
};

class UnionFind {
private:
    vector<int> parinte, rang;

public:
    UnionFind(int n) {
        parinte.resize(n);
        rang.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parinte[i] = i;
        }
    }

    int find(int x) {
        if (parinte[x] != x) {
            parinte[x] = find(parinte[x]);
        }
        return parinte[x];
    }

    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py) return false;

        if (rang[px] < rang[py]) {
            parinte[px] = py;
        }
        else if (rang[px] > rang[py]) {
            parinte[py] = px;
        }
        else {
            parinte[py] = px;
            rang[px]++;
        }
        return true;
    }
};

int main() {
    ifstream fin("arbore.in");
    ofstream fout("arbore.out");

    int V, E;

    fin >> V >> E;

    vector<Muchie> muchii;

    for (int i = 0; i < E; i++) {
        int u, v, cost;
        fin >> u >> v >> cost;
        muchii.push_back(Muchie(u, v, cost));
    }

    // Algoritmul Kruskal

    // Pasul 1: Sortăm muchiile după cost
    sort(muchii.begin(), muchii.end());

    // Pasul 2: Inițializăm Union-Find
    UnionFind uf(V);

    vector<Muchie> mst; // Arborele minim de acoperire
    int costTotal = 0;

    // Pasul 3: Parcurgem muchiile sortate
    for (const Muchie& muchie : muchii) {
        // Verificăm dacă muchia creează ciclu
        if (uf.unite(muchie.u, muchie.v)) {
            mst.push_back(muchie);
            costTotal += muchie.cost;

            // Dacă am găsit V-1 muchii, ne oprim
            if (mst.size() == V - 1) {
                break;
            }
        }
    }

    fout << "Cost total: " << costTotal << "\n";
    fout << "Numar de muchii: " << mst.size() << "\n";

    for (const Muchie& muchie : mst) {
        fout << muchie.u << " " << muchie.v << "\n";
    }

    fin.close();
    fout.close();

    return 0;
}