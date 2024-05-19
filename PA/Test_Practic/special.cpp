#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n;
    int k1, k2;
    vector<int> sir1, sir2;
    cin >> n >> k1 >> k2;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sir1.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sir2.push_back(x);
    }

    int i = 0, j = 0;
    int op = 0;
    while (i < n && j < n) {
        if (sir1[i] == sir2[j]) {
            i++;
            j++;
        } else {
            sir1[i] = sir2[j];
            op++;
            i++;
            j++;
        }
    }

    cout << op;

    return 0;
}