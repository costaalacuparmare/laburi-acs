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
    string caractere;
    vector<int> freq;

    void read_input() {
        ifstream fin("in");
        fin >> n >> k;
        fin >> caractere;
        caractere = " " + caractere; // Adaugare element fictiv -
        // indexare de la 1.
        freq.push_back(-1); // Adaugare element fictiv - indexare de la 1.
        for (int i = 1, f; i <= n; i++) {
            fin >> f;
            freq.push_back(f);
        }
        fin.close();
    }


    // n = number of characters
    // k = maximum number of consecutive characters
    // freq = frequency of each character
    void backtrack(vector<vector<char>>& all, vector<char>& sir, int pos) {
        if (pos >= k) {
            all.push_back(sir);
            return;
        }

        for (int i = 1; i <= n; i++) {
            if (freq[i] > 0 && (pos <= k || sir[pos - k] != caractere[i])) {
                sir[pos] = caractere[i];
                freq[i]--;
                backtrack(all, sir, pos + 1);
                freq[i]++;
            }
        }
    }





    // Construiti toate sirurile cu caracterele in stringul caractere
    // (indexat de la 1 la n), si frecventele in vectorul freq (indexat de la 1 la n),
    // stiind ca nu pot fi mai mult de K aparitii consecutive ale
    // aceluiasi caracter.
    //
    // Pentru a adauga un nou sir:
    //     vector<char> sir;
    //     all.push_back(sir);
    //

    vector<vector<char>> get_result() {
        vector<vector<char>> all;
        vector<char> sir(k, ' ');
        backtrack(all, sir, 1);
        for (size_t i = 0; i < all.size(); i++) {
            all[i].erase(all[i].begin());
        }
        return all;
    }

    void print_output(const vector<vector<char>>& result) {
        ofstream fout("out");
        fout << result.size() << '\n';
        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].size(); j++) {
                fout << result[i][j];
            }
            fout << '\n';
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