#include <bits/stdc++.h>
using namespace std;

struct Homework {
    int deadline;
    int score;

    Homework(int _deadline, int _score)
            : deadline(_deadline)
            , score(_score) { }
};

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n;
    vector<Homework> hws;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        for (int i = 0, deadline, score; i < n; i++) {
            fin >> deadline >> score;
            hws.push_back(Homework(deadline, score));
        }
        fin.close();
    }

    int get_result() {
        sort(hws.begin(), hws.end(), [](const Homework& a, const Homework& b) {
            return a.deadline < b.deadline;
        });

        vector<int> dp(n + 1, 0);

        for (const auto& hw : hws) {
            for (int d = hw.deadline; d >= 1; --d) {
                dp[d] = max(dp[d], dp[d - 1] + hw.score);
            }
        }

        return *max_element(dp.begin(), dp.end());
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
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
