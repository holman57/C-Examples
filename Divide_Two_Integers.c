/*
Given two integers dividend and divisor, divide two integers without using multiplication,
division and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero, which means losing its fractional part.
For example, truncate(8.345) = 8 and truncate(-2.7335) = -2.

Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = truncate(3.33333..) = 3.
Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = truncate(-2.33333..) = -2.
Note:

Both dividend and divisor will be 32-bit signed integers.
The divisor will never be 0.
Assume we are dealing with an environment which could only store
 integers within the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose of this problem,
 assume that your function returns 2^31 − 1 when the division result overflows.
 * */
int divide(int dividend, int divisor) {
    //special cases
    if (divisor == 0 || (dividend == INT_MIN && divisor == -1))
        return INT_MAX;

    // transform to unsigned int
    bool sign = (dividend > 0) ^(divisor > 0);
    unsigned int A = (divisor < 0) ? -divisor : divisor;
    unsigned int B = (dividend < 0) ? -dividend : dividend;
    int ret = 0;

    // shift 32 times
    for (int i = 31; i >= 0; i--) {
        if ((B >> i) >= A) {
            ret = (ret << 1) | 0x01;
            B -= (A << i);   // update B
        } else
            ret = ret << 1;
    }

    if (sign)
        ret = -ret;

    return ret;
}