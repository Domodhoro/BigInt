#include <iostream>
#include <stdexcept>

using std::cout;
using std::cerr;
using std::cin;
using std::exception;

#include "bigint.hpp"

int main() {
	try {
        BigInt x("10000000000000000000000000000000000000000"), y("1"), z;

        z = x - y;

        cout << "x + y = " << z;
        cin.get();

        return 0;
	} catch (const exception& e) {
        cerr << e.what();
        cin.get();

        return 1;
	}
}
