#include <iostream>
#include<cstring>
#include <fstream>

using namespace std;

ifstream in("graf.txt");

typedef struct
{
    int ind;
    int d;
    int f;
} nod;

typedef struct
{
    nod V[100];
    int adj[100][100];
    int n, m;          // n = numãr noduri, m = numãr muchii
} graf;



void DFS_VISIT(graf& g, int& time, int u, int visited[100])
{
    time = time + 1;
    g.V[u].d = time;
    visited[u] = 1;
    for (int i = 1; i <= g.n; i++)
    {
        if (g.adj[u][i] == 1 and visited[i] == 0)
        {
            DFS_VISIT(g, time, i, visited);
        }

    }
    time = time + 1;
    g.V[u].f = time;
    cout << u << " ";
}

void DFS(graf& g)
{
    int visited[100] = { 0 };
    int time = 0;
    for (int i = 1; i <= g.n; i++)
        if (visited[g.V[i].ind] == 0)
            DFS_VISIT(g, time, i, visited);
}
int main()
{
    graf g;


    in >> g.n;
    in >> g.m;


    int x, y;

    for (int i = 0; i < g.m; i++)
    {
        in >> x >> y;
        g.adj[x][y] = 1;
        g.adj[y][x] = 1; // Graful este neorientat
    }

    for (int i = 1; i <= g.n; i++)
    {
        g.V[i].ind = i;
    }

    DFS(g);

    cout << "\nRezultatele DFS \n";
    for (int i = 1; i <= g.n; i++)
    {
        cout << "Nod: " << i << ", Descoperit: " << g.V[i].d << ", Finalizat: " << g.V[i].f << endl;
    }

    return 0;
}