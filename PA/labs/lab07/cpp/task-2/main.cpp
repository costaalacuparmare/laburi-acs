#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
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

    // Gasiti toate nodurile critice ale grafului neorientat stocat cu liste de adiacenta in adj.
    // Rezultatul se va returna sub forma unui vector cu toate punctele critice (ordinea nu conteaza).
    // Indicație: Folosiți algoritmul lui Tarjan pentru CV.

    void tarjan(int node, vector<int>& all_cvs, vector<int>& idx,
                vector<int>& low, vector<int>& parent, vector<bool>& visited,
                int& time) {
        idx[node] = low[node] = time++;
        visited[node] = true;
        int children = 0;
        bool is_critical = false;
        for (auto neigh : adj[node]) {
            if (!visited[neigh]) {
                children++;
                parent[neigh] = node;
                tarjan(neigh, all_cvs, idx, low, parent, visited, time);
                low[node] = min(low[node], low[neigh]);
                if (parent[node] == -1 && children > 1) {
                    is_critical = true;
                }
                if (parent[node] != -1 && low[neigh] >= idx[node]) {
                    is_critical = true;
                }
            } else if (neigh != parent[node]) {
                low[node] = min(low[node], idx[neigh]);
            }
        }
        if ((parent[node] == -1 && children > 1) || (parent[node] != -1 &&
            is_critical)) {
            all_cvs.push_back(node);
        }
    }


    vector<int> get_result() {
        vector<int> all_cvs;
        vector<int> idx(n + 1, -1);
        vector<int> low(n + 1, -1);
        vector<int> parent(n + 1, -1);
        vector<bool> visited(n + 1, false);
        int time = 0;
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                tarjan(i, all_cvs, idx, low, parent, visited, time);
            }
        }
        return all_cvs;
    }

    void print_output(const vector<int>& all_cvs) {
        ofstream fout("out");
        for (auto cv : all_cvs) {
            fout << cv << ' ';
        }
        fout << '\n';
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
