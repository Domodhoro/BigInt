#include <iostream>

#include "bigint.hpp"

int main() {
	try {
        BigInt x("100000000000000000000000000000000000000000000000000000000000"), y("1");

        x += y;

        std::cout << "x + y = " << x << "\n";
        std::cin.get();
        return 0;
	} catch (const std::exception& e) {
        std::cerr << e.what();
        std::cin.get();
        return 1;
	}
}
