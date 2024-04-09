#include <bits/stdc++.h>
using namespace std;

// constanta modulo folosita in aceasta problema
#define MOD ((int)1e9 + 7)
// sau
// #define MOD 100000007
// (varianta 2 e mai ușor de busit, sesizați? :p)

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n;
    string expr;

    void read_input() {
        ifstream fin("in");
        fin >> n >> expr;
        expr = " " + expr; // adaugare caracter fictiv - indexare de la 1
        fin.close();
    }

    int get_result() {
        // Calculati numarul de parantezari ale expresiei date astfel incat
        // rezultatul sa dea true si returnati restul impartirii numarului
        // la 10^9 + 7 (vezi macro-ul MOD).
        return bool_expression();
    }

    bool is_operator(char op) {
        return op == '&' || op == '|' || op == '^';
    }

    bool is_operand(char op) {
        return op == 'T' || op == 'F';
    }

    bool evaluate(char op, int L, int R) {
        if (op == '&')
            return L & R;
        if (op == '|')
            return L | R;
        if (op == '^')
            return L ^ R;

        return false;
    }

    int bool_expression() {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(2, 0)));

        for (int i = 1; i <= n; i += 2) {
            dp[i][i][0] = (expr[i] == 'F');
            dp[i][i][1] = (expr[i] == 'T');
        }

        for (int len = 2; len <= n; ++len) {
            for (int i = 1; i + len - 1 <= n; ++i) {
                int j = i + len - 1;
                for (int k = i + 1; k < j; ++k) {
                    if (!is_operator(expr[k])) {
                        continue;
                    }
                    char op = expr[k];
                    for (int lv = 0; lv <= 1; ++lv) {
                        for (int rv = 0; rv <= 1; ++rv) {
                            bool v = evaluate(op, lv, rv);
                            int add = (1LL * dp[i][k - 1][lv] * dp[k + 1][j][rv]) % MOD;
                            dp[i][j][v] = (dp[i][j][v] + add) % MOD;
                        }
                    }
                }
            }
        }
        return dp[1][n][1];
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << '\n';
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
