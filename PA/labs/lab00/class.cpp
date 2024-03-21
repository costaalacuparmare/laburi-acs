#include <iostream>

class Gigel {
    int x = 100; // private because is in a class;
    // if Gigel was struct, x was public.
public:
    void show() {
        std::cout << "x is " << x << "\n";
    }
};

int main() {
    Gigel g;
    g.show(); // print "x is 100"
    return 0;
}
