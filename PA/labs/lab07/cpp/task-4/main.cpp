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


    // vector pentru a memora timpul de descoperire a fiecarui nod
    vector<int> disc;

    // vector pentru a memora timpul de terminare a fiecarui nod
    vector<int> finish;

    // vector pentru a memora cel mai mic timp de descoperire al unui nod
    // accesibil din subarborele unui nod
    vector<int> low;

    // vector pentru a memora daca un nod este sau nu punct de articulatie
    vector<bool> is_articulation;

    // vector pentru a memora muchiile critice (ponturi)
    vector<Edge> bridges;

    // stiva folosita pentru a retine nodurile dintr-un BCC
    stack<Edge> edge_stack;

    // vector pentru a memora toate BCC-urile
    vector<vector<int>> all_bccs;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        disc.resize(n + 1);
        finish.resize(n + 1);
        low.resize(n + 1);
        is_articulation.resize(n + 1, false);

        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y; // muchia (x, y)
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }


    // Găsiți componentele biconexe (BCC) ale grafului neorientat cu n noduri, stocat în adj.
    // Rezultatul se va returna sub forma unui vector, fiecare element fiind un BCC (adică tot un vector).
    // * nodurile dintr-un BCC pot fi găsite în orice ordine
    // * BCC-urile din graf pot fi găsite în orice ordine
    // Indicație: Folosiți algoritmul lui Tarjan pentru BCC.

    void tarjan(int u, int parent, int &time) {
        disc[u] = low[u] = ++time;
        int children = 0;

        for (int v : adj[u]) {
            if (v == parent)
                continue;
            if (!disc[v]) {
                children++;
                edge_stack.push(Edge(u, v));
                tarjan(v, u, time);
                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u])
                    bridges.push_back(Edge(u, v));

                if (parent != -1 && low[v] >= disc[u])
                    is_articulation[u] = true;

                if (low[v] >= disc[u]) {
                    vector<int> bcc_nodes;
                    Edge e;
                    do {
                        e = edge_stack.top();
                        edge_stack.pop();
                        if (find(bcc_nodes.begin(), bcc_nodes.end(), e.x) == bcc_nodes.end())
                            bcc_nodes.push_back(e.x);
                        if (find(bcc_nodes.begin(), bcc_nodes.end(), e.y) == bcc_nodes.end())
                            bcc_nodes.push_back(e.y);
                    } while (!(e.x == u && e.y == v) && !(e.x == v && e.y == u));
                    if (find(bcc_nodes.begin(), bcc_nodes.end(), u) == bcc_nodes.end())
                        bcc_nodes.push_back(u); // Adaugam nodul u in BCC
                    sort(bcc_nodes.begin(), bcc_nodes.end());
                    all_bccs.push_back(bcc_nodes);
                }
            } else if (disc[v] < disc[u]) {
                low[u] = min(low[u], disc[v]);
                edge_stack.push(Edge(u, v));
            }
        }

        if (parent == -1 && children > 1)
            is_articulation[u] = true;
    }


    vector<vector<int>> get_result() {
        int time = 0;
        for (int i = 1; i <= n; ++i) {
            if (!disc[i]) {
                tarjan(i, -1, time);
            }
        }

        vector<vector<int>> remaining_bccs;
        while (!edge_stack.empty()) {
            Edge e = edge_stack.top();
            edge_stack.pop();
            vector<int> bcc_nodes = {e.x, e.y};
            remaining_bccs.push_back(bcc_nodes);
        }
        if (!remaining_bccs.empty()) {
            all_bccs.push_back(remaining_bccs.back());
            remaining_bccs.pop_back();
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