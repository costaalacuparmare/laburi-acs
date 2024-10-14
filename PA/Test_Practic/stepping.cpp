#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

#define INF (1 << 30)


int main() {
    int n, start;
    cin >> n;
    cin >> start;

    vector<pair<int, int>> graph[n];

    for (int i = 0; i < n - 1; i++) {
        int nr_jumps;
        cin >> nr_jumps;

        for (int j = 0; j < nr_jumps; j++) {
            int jump;
            cin >> jump;

            if (i + jump < n) {
                graph[i].push_back({i + jump, 1});
            }
        }
    }

    vector<int> d(n, INF);
    vector<int> p(n, 0);
    set<pair<int, int>> pq;

    d[start] = 0;
    pq.insert({d[start], start});

    while (!pq.empty()) {
        auto top = pq.begin();
        const auto [_, node] = *top;
        pq.erase(top);

        for (const auto& [neigh, w] : graph[node]) {
            if (d[node] + w < d[neigh]) {
                pq.erase({d[neigh], neigh});

                d[neigh] = d[node] + w;
                p[neigh] = node;

                pq.insert({d[neigh], neigh});
            }
        }
    }

    for (int node = 0; node < n; node++) {
        if (d[node] == INF) {
            d[node] = -1;
        }
    }

    cout << d[n - 1];

    return 0;
}