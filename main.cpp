#include <iostream>
#include <stdexcept>

#include "bigint.hpp"

int main() {
	try {
        Math::BigInt x {"1000000"}, y {"1"};

        auto z {x - y};

        std::cout << "z = " << z;
        std::cin.get();

        return 0;
	} catch (const std::exception& e) {
        std::cerr << e.what();
        std::cin.get();

        return 1;
	}
}
