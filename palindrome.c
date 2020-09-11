#include <stdbool.h>
#include <stdio.h>

bool isPalindrome(int x) {
    int orig, temp;
    long compare;
    compare = 0;
    orig = x;
    if (x < 0)
        return false;
    while (orig != 0) {
        temp = orig % 10;
        compare = compare * 10 + temp;
        orig = orig / 10;
    }
    printf("compare: %ld\n", compare);
    if (compare == x) {
        return true;
    } else {
        return false;
    }
}
