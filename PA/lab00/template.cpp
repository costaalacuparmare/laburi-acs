#include <iostream>

// generic maximum function: a and b have the same template type T
template <typename T>
T my_max (T a, T b) {
    return (a > b ? a : b);
}

int main() {
    //  usage example for T = int
    std::cout << my_max<int>(2, 3) << "\n";
    // or let to compile to automatically determine the T type from the passed values
    std::cout << my_max(2, 3) << "\n";

    // usage example for T = double
    std::cout << my_max(3.4, 5.6) << "\n";

    // usage example for T = char
    std::cout << my_max('a', 'b') << "\n";
    return 0;
}