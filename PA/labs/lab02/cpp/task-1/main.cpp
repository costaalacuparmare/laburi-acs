#include <bits/stdc++.h>
using namespace std;

struct Object {
    int weight;
    int price;

    Object(int _weight, int _price)
            : weight(_weight)
            , price(_price) { }
};

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, w;
    vector<Object> objs;

    void read_input() {
        ifstream fin("in");
        fin >> n >> w;
        for (int i = 0, weight, price; i < n; i++) {
            fin >> weight >> price;
            objs.push_back(Object(weight, price));
        }
        fin.close();
    }

    double get_result() {
        sort(objs.begin(), objs.end(), [](const Object& a, const Object& b) {
            return (double) a.price / a.weight > (double) b.price / b.weight;});
        double result = 0;
        for (int i = 0; i < n; i++) {
            if (objs[i].weight <= w) {
                result += objs[i].price;
                w -= objs[i].weight;
            } else {
                result += (double) w / objs[i].weight * objs[i].price;
                break;
            }
        }
        return result;
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
