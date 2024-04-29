#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    struct Edge {
        int x;
        int y;

        Edge() { }
        Edge(int x, int y)
            : x(x)
            , y(y) { }
    };

    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y; // muchia (x, y)
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }

    // Gasiti toate muchiile critice ale grafului neorientat stocat cu liste de adiacenta in adj.
    // Rezultatul se va returna sub forma unui vector cu toate muchille critice (ordinea lor nu conteaza).
    // Indicație: Folosiți algoritmul lui Tarjan pentru CE.

    void tarjan(int node, vector<int>& low, vector<int>& disc,
                vector<int>& parent, vector<bool>& visited,
                int& time, vector<Edge>& all_ces) {
        visited[node] = true;
        disc[node] = low[node] = ++time;
        for (auto& neigh : adj[node]) {
            if (!visited[neigh]) {
                parent[neigh] = node;
                tarjan(neigh, low, disc, parent, visited, time, all_ces);
                low[node] = min(low[node], low[neigh]);
                if (low[neigh] > disc[node]) {
                    all_ces.push_back(Edge(node, neigh));
                }
            } else if (neigh != parent[node]) {
                low[node] = min(low[node], disc[neigh]);
            }
        }
    }

    vector<Edge> get_result() {
        vector<Edge> all_ces;
        vector<int> low(n + 1, 0);
        vector<int> disc(n + 1, 0);
        vector<int> parent(n + 1, -1);
        vector<bool> visited(n + 1, false);
        int time = 0;
        // use tarjan
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                tarjan(i, low, disc, parent, visited, time, all_ces);
            }
        }
        return all_ces;
    }

    void print_output(const vector<Edge>& all_ces) {
        ofstream fout("out");
        fout << all_ces.size() << '\n';
        for (auto& ce : all_ces) {
            fout << ce.x << ' ' << ce.y << '\n';
        }
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
