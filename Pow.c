double paw(double x, int n) {
    double ans = 1;

    if (n == 0) {
        return 1;
    }

    ans = paw(x, n / 2);
    if (n % 2 == 0) {
        return ans * ans;
    } else {
        return ans * ans * x;
    }
}


double myPow(double x, int n) {
    double ans = 0;

    if (x == 1 && n < 0) {
        return 1;
    }

    if (x != 0 && n == -2147483648) {
        n = 2147483648 / 2;
        x = 1 / x;
        ans = paw(x, n);
        return ans;
    }


    if (n < 0) {
        x = 1 / x;
        n = n * -1;
    }

    ans = paw(x, n);

    return ans;

}