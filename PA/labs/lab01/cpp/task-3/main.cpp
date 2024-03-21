#include <bits/stdc++.h>

using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, x, y;

    void read_input() {
        ifstream fin("in");
        fin >> n >> x >> y;
        fin.close();

    }

    int get_value(int n, int x, int y) {
        if (n == 1) {
            if (x == 1 && y == 1)
                return 1;
            if (x == 1 && y == 2)
                return 2;
            if (x == 2 && y == 1)
                return 3;
            if (x == 2 && y == 2)
                return 4;
        }

        int size = 1 << n; // Equivalent to 2^n

        if (x <= size / 2 && y <= size / 2) {
            return get_value(n - 1, x, y);
        } else if (x <= size / 2 && y > size / 2) {
            return (size / 2) * (size / 2) + get_value(n - 1, x, y - size / 2);
        } else if (x > size / 2 && y <= size / 2) {
            return 2 * (size / 2) * (size / 2) + get_value(n - 1, x - size / 2, y);
        } else {
            return 3 * (size / 2) * (size / 2) + get_value(n - 1, x - size / 2, y - size / 2);
        }
    }

    int get_result() { return get_value(n, x, y); }

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
