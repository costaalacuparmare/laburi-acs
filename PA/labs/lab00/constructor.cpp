#include <iostream>

class Gigel {
public:
    Gigel() {
        std::cout << "Gigel()\n";
    }

    Gigel(int x) {
        std::cout << "Gigel(" << x << ")\n";
    }
};

int main() {
    Gigel g;         // print "Gigel()"
    Gigel g4(5);     // print "Gigel(5)"
}