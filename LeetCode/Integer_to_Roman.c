/*
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

        Symbol       Value
        I             1
        V             5
        X             10
        L             50
        C             100
        D             500
        M             1000
 */
char *intToRoman(int num)
{
    // max is an arbitrary starting size for output which is a dynamicly sized char array with length len
    int max = 4, len = 0, shift = 0, cur;
    char *output = (char *) malloc(max * sizeof(*output));
    assert(output != NULL);

    char symbols[8] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    int dist[10] = {1, 11, 111, 12, 2, 21, 211, 2111, 13, 3};

    // Look through the digits in num one at a time
    while (num)
    {
        if (num % 10 != 0)
        {
            // Find the corresponding roman numeral chars for the digit
            cur = dist[num % 10 - 1];
            while (cur)
            {
                // Double size of output array if necessary
                if (len + 1 >= max)
                {
                    output = (char *) realloc(output, (max *= 2) * sizeof(*output));
                    assert(output != NULL);
                }
                output[len++] = symbols[cur % 10 - 1 + shift];
                cur /= 10;
            }
        }
        num /= 10;
        shift += 2;
    }
    output[len] = '\0';

    // Reverse the output string
    int temp;
    for (int i = 0; i < len / 2; i++)
    {
        temp = output[i];
        output[i] = output[len - 1 - i];
        output[len - 1 - i] = temp;
    }
    return output;
}