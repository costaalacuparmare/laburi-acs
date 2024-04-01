#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    double n;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    double get_result() {
        // TODO: Calculati sqrt(n) cu o precizie de 0.001
        // Precizie de 10^-x = |rezultatul vostru - rezultatul corect| <= 10^-x
        double left = 0, right = n, mid;
        if (n < 1) {
            left = n;
            right = 1;
        }
        while (n - left * left > 0.001) {
            mid = (left + right) / 2;
            if (mid * mid < n) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return left;
    }

    void print_output(double result) {
        ofstream fout("out");
        fout << setprecision(4) << fixed << result;
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