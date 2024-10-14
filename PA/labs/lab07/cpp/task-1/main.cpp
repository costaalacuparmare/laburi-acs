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
            fin >> x >> y;
            adj[x].push_back(y); // arc (x, y)
        }
        fin.close();
    }

    // Găsiți componentele tare conexe  (CTC / SCC) ale grafului orientat cu n noduri, stocat în adj.
    // Rezultatul se va returna sub forma unui vector, fiecare element fiind un SCC (adică tot un vector).
    // * nodurile dintr-un SCC pot fi găsite în orice ordine
    // * SCC-urile din graf pot fi găsite în orice ordine
    // Indicație: Folosiți algoritmul lui Tarjan pentru SCC.

    void tarjan(int node, vector<int>& idx, vector<int>& low, int& idx_counter,
                stack<int>& st, vector<bool>& on_stack,
                vector<vector<int>>& all_sccs) {
        idx[node] = low[node] = idx_counter++;
        st.push(node);
        on_stack[node] = true;
        for (auto neigh : adj[node]) {
            if (idx[neigh] == -1) {
                tarjan(neigh, idx, low, idx_counter, st, on_stack, all_sccs);
                low[node] = min(low[node], low[neigh]);
            } else if (on_stack[neigh]) {
                low[node] = min(low[node], idx[neigh]);
            }
        }
        if (idx[node] == low[node]) {
            vector<int> scc;
            int top;
            do {
                top = st.top();
                st.pop();
                on_stack[top] = false;
                scc.push_back(top);
            } while (top != node);
            all_sccs.push_back(scc);
        }
    }

    vector<vector<int>> get_result() {
        vector<vector<int>> all_sccs;
        stack<int> st;
        vector<int> idx(n + 1, -1);
        vector<int> low(n + 1, -1);
        vector<bool> on_stack(n + 1, false);
        int idx_counter = 0;
        for (int i = 1; i <= n; i++) {
            if (idx[i] == -1) {
                tarjan(i, idx, low, idx_counter, st, on_stack, all_sccs);
            }
        }
        return all_sccs;
    }

    void print_output(const vector<vector<int>>& all_sccs) {
        ofstream fout("out");
        fout << all_sccs.size() << '\n';
        for (const auto& scc : all_sccs) {
            for (auto node : scc) {
                fout << node << ' ';
            }
            fout << '\n';
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
