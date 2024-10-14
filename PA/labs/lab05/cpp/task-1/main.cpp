#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, k;

    void read_input() {
        ifstream fin("in");
        fin>> n >> k;
        fin.close();
    }

    void backtrack(vector<vector<int>>& all, vector<int>& arrangement) {
        if (arrangement.size() == k) {
            all.push_back(arrangement);
            return;
        }

        for (int i = 1; i <= n; i++) {
            bool ok = true;
            for (int j = 0; j < arrangement.size(); j++) {
                if (arrangement[j] == i) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                arrangement.push_back(i);
                backtrack(all, arrangement);
                arrangement.pop_back();
            }
        }
    }

    // Construiti toate aranjamentele de N luate cate K ale
    // multimii {1, ..., N}.
    //
    // Pentru a adauga un nou aranjament:
    //     vector<int> aranjament;
    //     all.push_back(aranjament);
    vector<vector<int>> get_result() {
        vector<vector<int>> all;
        vector<int> arrangement;
        backtrack(all, arrangement);
        return all;
    }

    void print_output(const vector<vector<int>>& result) {
        ofstream fout("out");
        fout << result.size() << '\n';
        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].size(); j++) {
                fout << result[i][j] << (j + 1 != result[i].size() ? ' ' : '\n');
            }
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
