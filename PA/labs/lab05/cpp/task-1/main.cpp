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
        //ifstream fin("in");
        cin >> n >> k;
        //fin.close();
    }

    void backtrack(vector<vector<int>>& all, vector<int>& arrangement, int start) {
        if (arrangement.size() == k) {
            all.push_back(arrangement);
            return;
        }

        for (int i = start; i <= n; ++i) {
            arrangement.push_back(i);
            backtrack(all, arrangement, i + 1);
            arrangement.pop_back();
        }
    }

    vector<vector<int>> get_result() {
        vector<vector<int>> all;
        vector<int> arrangement;
        backtrack(all, arrangement, 1);
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
