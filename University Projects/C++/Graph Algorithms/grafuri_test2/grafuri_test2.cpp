#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>

const int INF = 1e9;

using namespace std;

std::ifstream fin("arb.in");
std::ofstream fout("arb.out");

struct Edge {
    int u, v, cost, id;
};

int main() {
    int n, m;
    fin >> n >> m;

    std::vector<Edge> all_edges(m);
    for (int i = 0; i < m; ++i) {
        fin >> all_edges[i].u >> all_edges[i].v >> all_edges[i].cost;
        all_edges[i].id = i;
    }

    for (int i = 0; i < n - 1; ++i) {

        std::vector<int> dist(n, INF);
        std::vector<bool> visited(n, false);
        std::vector<int> edge_used_id(n, -1);

        dist[0] = 0;
        long long total_cost = 0;

        for (int count = 0; count < n; ++count) {
            int u = -1;
            for (int j = 0; j < n; ++j) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (u == -1 || dist[u] == INF) {
                break;
            }

            visited[u] = true;
            total_cost += dist[u];

            for (const auto& edge : all_edges) {
                if (edge.id == i) continue;

                int v1 = edge.u;
                int v2 = edge.v;
                int cost = edge.cost;

                if (v1 == u && !visited[v2] && cost < dist[v2]) {
                    dist[v2] = cost;
                    edge_used_id[v2] = edge.id;
                }
                if (v2 == u && !visited[v1] && cost < dist[v1]) {
                    dist[v1] = cost;
                    edge_used_id[v1] = edge.id;
                }
            }
        }

        int replacement_edge_id = -1;
        for (int j = 0; j < n; ++j) {
            if (edge_used_id[j] >= n - 1) {
                replacement_edge_id = edge_used_id[j];
                break;
            }
        }

        fout << replacement_edge_id << std::endl;
    }

    return 0;
}