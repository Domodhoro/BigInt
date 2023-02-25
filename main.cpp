/*
    MIT License

    Copyright (c) 2023 Guilherme M. Aguiar (guilhermemaguiar2022@gmail.com)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

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
