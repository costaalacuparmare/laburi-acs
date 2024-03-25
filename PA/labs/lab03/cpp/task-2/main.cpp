#include <bits/stdc++.h>
using namespace std;

struct Result {
    int len; // rezultat pentru cerinta 1
    vector<int> subsequence; // rezultat pentru cerinta 2
};

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, m;
    vector<int> v;
    vector<int> w;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;

        v.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= n; i++) {
            fin >> e;
            v.push_back(e);
        }

        w.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= m; i++) {
            fin >> e;
            w.push_back(e);
        }

        fin.close();
    }

    Result get_result() {
        Result result;
        result.len = 0;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        vector<vector<int>> path(n + 1, vector<int>(m + 1, -1));
        for (int i = 0; i <=n; i++) {
            dp[i][0] = 0;
        }
        for (int i = 0; i <=m; i++) {
            dp[0][i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (v[i] == w[j]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    path[i][j] = 0;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    if (dp[i][j] == dp[i - 1][j]) {
                        path[i][j] = 1;
                    } else {
                        path[i][j] = 2;
                    }
                }
            }
        }

        vector<int> subsequence;
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (path[i][j] == 0) {
                subsequence.push_back(v[i]);
                i--;
                j--;
            } else if (path[i][j] == 1) {
                i--;
            } else {
                j--;
            }
        }

        reverse(subsequence.begin(), subsequence.end());
        result.len = dp[n][m];
        result.subsequence = subsequence;
        return result;
    }

    void print_output(Result result) {
        ofstream fout("out");
        fout << result.len << '\n';
        for (int x : result.subsequence) {
            fout << x << ' ';
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
