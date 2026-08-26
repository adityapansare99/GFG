#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isNegativeWeightCycle(int V, vector<vector<int>> &edges)
    {
        vector<long long> dist(V, 0);

        // Relax all edges V - 1 times
        for (int i = 0; i < V - 1; i++)
        {
            bool changed = false;
            for (auto &it : edges)
            {
                int u = it[0];
                int v = it[1];
                int w = it[2];
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    changed = true;
                }
            }
            if (!changed)
            {
                break;
            }
        }

        // One more relaxation to detect a negative cycle
        for (auto &it : edges)
        {
            int u = it[0];
            int v = it[1];
            int w = it[2];
            if (dist[u] + w < dist[v])
            {
                return true;
            }
        }
        return false;
    }
};