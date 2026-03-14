#include <iostream>
#include <fstream>
#include <cstring>
#define INFINITY 1000
#include <queue>
using namespace std;
using std::queue;
ifstream in("graf.txt");

struct nod
{
    int ind;
    int d;
};

struct graf
{
    int n, m;
    nod V[100];
    int adj[100][100];
};

void BFS(graf& g, int s)
{

    for (int i = 1; i <= g.n; i++)
    {
        g.V[i].d = INFINITY;
    }

    int visited[100] = { 0 };
    visited[s] = 1;
    g.V[s].d = 0;
    queue <int> q;
    q.push(s);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int i = 1; i <= g.n; i++)
            if (g.adj[v][i] == 1)
            {
                if (visited[i] == 0)
                {
                    visited[i] = 1;
                    g.V[i].d = g.V[v].d + 1;
                    q.push(i);
                }
            }
        cout << v << " ";
    }
}

int main()
{
    int s, x, y;
    graf g;
    in >> g.m >> g.n;
    in >> s;

    memset(g.adj, 0, sizeof(g.adj));

    for (int i = 1; i <= g.m; i++)
    {
        in >> x >> y;
        g.adj[x][y] = g.adj[y][x] = 1;
    }

    for (int i = 1; i <= g.n; i++)
    {
        g.V[i].ind = i;
    }

    BFS(g, s);

    cout << "\nRezultatele BFS pornind din nodul " << s << ":\n";
    for (int i = 1; i <= g.n; i++)
    {
        cout << "Nod: " << i << ", Distanta: " << (g.V[i].d == INFINITY ? -1 : g.V[i].d) << endl;
    }
    return 0;
}