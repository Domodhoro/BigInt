#ifdef __cplusplus

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
}

#endif

#include <iostream>
#include <string>
#include <algorithm>

static void error_log(const char *file, const int line, const char *description) {
    puts  ("A failure occurred!");
    printf("File:        %s.\n", file);
    printf("Line:        %i.\n", line);
    printf("Description: %s.\n", description);

    exit(EXIT_FAILURE);
}

#include "./bigint.hpp"

int main(int argc, char *argv[]) {
	math::bigint x {"100000000000000000000000000"};
	math::bigint y {"123456789"};

    std::cout << x << " + " << y << " = " << x + y << '\n';

    sleep(5);

    return 0;
}
