// Given an input string (s) and a pattern (p), implement regular expression 
// matching with support for '.' and '*'.

// '.' Matches any single character.
// '*' Matches zero or more of the preceding element.
bool isMatch(char *s, char *p)
{
    int len_s, len_p;

    len_s = strlen(s);
    len_p = strlen(p);

    if (len_s == 0 && len_p == 0)
        return true;

    if (len_s > 0 && len_p == 0)
        return false;

    if (len_s == 0 && len_p > 0)
    {
        if (len_p >= 2 && p[1] == '*')
            return isMatch(s, &p[2]);
        else
            return false;
    }

    assert(len_s > 0 && len_p > 0);

    if (len_p >= 2 && p[1] == '*')
    {
        if (s[0] == p[0] || p[0] == '.')
            return isMatch(&s[1], p) || isMatch(s, &p[2]);
        else
            return isMatch(s, &p[2]);
    } else
    {
        if (s[0] == p[0] || p[0] == '.')
            return isMatch(&s[1], &p[1]);
        else
            return false;
    }
}
