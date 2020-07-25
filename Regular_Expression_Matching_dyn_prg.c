// Given an input string (s) and a pattern (p), implement regular expression 
// matching with support for '.' and '*'.

// '.' Matches any single character.
// '*' Matches zero or more of the preceding element.
bool isMatch(char *s, char *p)
{
    int slen, plen;
    int si, pi;
    int **dp;

    slen = strlen(s);
    plen = strlen(p);

    dp = calloc(slen + 1, sizeof(int *));
    for (si = 0; si <= slen; si++)
        dp[si] = calloc(plen + 1, sizeof(int));

    dp[0][0] = true;
    // if si > 0 and pi == 0: false
    for (si = 1; si <= slen; si++)
        dp[si][0] = false;

    for (si = 0; si <= slen; si++)
    {
        for (pi = 1; pi <= plen; pi++)
        {
            if (si == 0)
            {
                if (p[pi - 1] == '*')
                {
                    dp[0][pi] = dp[0][pi - 2];
                } else
                {
                    dp[0][pi] = false;
                }
            } else if (s[si - 1] == p[pi - 1] || p[pi - 1] == '.')
            {
                if (pi < plen && p[pi] == '*')
                    dp[si][pi] = false;
                else
                    dp[si][pi] = dp[si - 1][pi - 1];
            } else if (p[pi - 1] == '*')
            {
                assert(pi > 1);
                if (s[si - 1] == p[pi - 2] || p[pi - 2] == '.')
                {
                    dp[si][pi] = dp[si][pi - 2] || dp[si - 1][pi];
                } else
                {
                    dp[si][pi] = dp[si][pi - 2];
                }
            } else
            {
                dp[si][pi] = false;
            }
        }
    }

    return dp[slen][plen];
}
