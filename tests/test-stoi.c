#include <stdlib.h>
#include <limits.h>

#include "algorithms/stoi.h"
#include "utils.h"

int main(void) {

    ut_assert(stoi("0") == 0);
    ut_assert(stoi("1") == 1);
    ut_assert(stoi("2") == 2);
    ut_assert(stoi("3") == 3);
    ut_assert(stoi("4") == 4);
    ut_assert(stoi("5") == 5);
    ut_assert(stoi("6") == 6);
    ut_assert(stoi("7") == 7);
    ut_assert(stoi("8") == 8);
    ut_assert(stoi("9") == 9);
    ut_assert(stoi("10") == 10);

    ut_assert(stoi("+10") == 10);
    ut_assert(stoi("  10") == 10);
    ut_assert(stoi("  +10") == 10);

    ut_assert(stoi("-250") == -250);
    ut_assert(stoi(" -1000") == -1000);
    ut_assert(stoi("  -500") == -500);

    ut_assert(stoi("") == 0);
    ut_assert(stoi("febits") == 0);
    ut_assert(stoi("feklipe") == 0);

    ut_assert(stoi("2147483647") == INT_MAX);
    ut_assert(stoi("-2147483648") == INT_MIN);

    ut_assert(stoi("  +2147483647") == INT_MAX);
    ut_assert(stoi("   -2147483648") == INT_MIN);

    return EXIT_SUCCESS;
}
