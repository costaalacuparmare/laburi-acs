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

        bool operator==(const Edge& other) { return x == other.x && y == other.y; }
        bool operator!=(const Edge& other) { return !(*this == other); }
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

    void tarjan(int node, int parent, stack<Edge>& st, vector<int>& idx, vector<int>& low, vector<bool>& is_articulation, int& idx_counter, vector<vector<int>>& all_bccs) {
        idx[node] = low[node] = ++idx_counter;
        int children = 0;
        for (auto neigh : adj[node]) {
            if (neigh == parent) {
                continue;
            }
            if (idx[neigh] == -1) {
                st.push(Edge(node, neigh));
                children++;
                tarjan(neigh, node, st, idx, low, is_articulation, idx_counter, all_bccs);
                low[node] = min(low[node], low[neigh]);
                if ((parent == -1 && children > 1) || (parent != -1 && low[neigh] >= idx[node])) {
                    is_articulation[node] = true;
                    vector<int> bcc;
                    while (st.top() != Edge(node, neigh)) {
                        bcc.push_back(st.top().x);
                        bcc.push_back(st.top().y);
                        st.pop();
                    }
                    bcc.push_back(st.top().x);
                    bcc.push_back(st.top().y);
                    st.pop();
                    all_bccs.push_back(bcc);
                }
            } else {
                low[node] = min(low[node], idx[neigh]);
                if (idx[neigh] < idx[node]) {
                    st.push(Edge(node, neigh));
                }
            }
        }
    }

    vector<vector<int>> get_result() {
        // Găsiți componentele biconexe (BCC) ale grafului neorientat cu n noduri, stocat în adj.
        // Rezultatul se va returna sub forma unui vector, fiecare element fiind un BCC (adică tot un vector).
        // * nodurile dintr-un BCC pot fi găsite în orice ordine
        // * BCC-urile din graf pot fi găsite în orice ordine
        // Indicație: Folosiți algoritmul lui Tarjan pentru BCC.

        vector<vector<int>> all_bccs;
        stack<Edge> st;
        vector<int> idx(n + 1, -1);
        vector<int> low(n + 1, -1);
        vector<bool> is_articulation(n + 1, false);
        int idx_counter = 0;
        for (int i = 1; i <= n; i++) {
            if (idx[i] == -1) {
                tarjan(i, -1, st, idx, low, is_articulation, idx_counter, all_bccs);
            }
        }
        return all_bccs;
    }

    void print_output(const vector<vector<int>>& all_bccs) {
        ofstream fout("out");
        fout << all_bccs.size() << '\n';
        for (auto& bcc : all_bccs) {
            for (auto node : bcc) {
                fout << node << " ";
            }
            fout << "\n";
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
