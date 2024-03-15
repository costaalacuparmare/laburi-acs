#include <iostream>

using namespace std;

struct Complex {
    double re, im;

    void print() const {
        // the im and re members for the current Complex object are accessed
        cout << re << "+" << im << "i" << "\n";
    }
};

int main()
{
    Complex c;
    c.re = 1;
    c.im = 2;
    c.print();
    return 0;
}