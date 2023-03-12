#ifdef __cplusplus

extern "C" {
#include <stdio.h>
#include <stdlib.h>
}

#endif

#include <iostream>
#include <string>
#include <algorithm>

struct my_exception {
    my_exception(const char *file, int line, const char *description) {
        printf("Ops! Uma falha ocorreu...\n\n");
        printf("File:        %s\n", file);
        printf("Line:        %i\n", line);
        printf("Description: %s\n", description);
    }

    ~my_exception() {
        exit(EXIT_FAILURE);
    }
};

#include "./bigint.hpp"

int main(int argc, char *argv[]) {
	math::bigint x {"100000000000000000000000000"};
	math::bigint y {"123456789"};

    std::cout << x << " + " << y << " = " << x + y << '\n';

    std::cin.get();

    return 0;
}
