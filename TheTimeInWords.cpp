#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'timeInWords' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER h
 *  2. INTEGER m
 */

string timeInWords(int h, int m) {
    // Words for numbers 1 to 29
    vector<string> words = {
        "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
        "eleven", "twelve", "thirteen", "fourteen", "quarter", "sixteen", "seventeen",
        "eighteen", "nineteen", "twenty", "twenty one", "twenty two", "twenty three",
        "twenty four", "twenty five", "twenty six", "twenty seven", "twenty eight", "twenty nine"
    };

    if (m == 0) {
        // Exactly on the hour
        return words[h] + " o' clock";
    } else if (m <= 30) {
        // Minutes past the hour
        if (m == 15) {
            return "quarter past " + words[h];
        } else if (m == 30) {
            return "half past " + words[h];
        } else if (m == 1) {
            return "one minute past " + words[h];
        } else {
            return words[m] + " minutes past " + words[h];
        }
    } else {
        // Minutes to the next hour
        int minutes_to = 60 - m;
        int next_hour = (h % 12) + 1; // Handle 12-hour format

        if (minutes_to == 15) {
            return "quarter to " + words[next_hour];
        } else if (minutes_to == 1) {
            return "one minute to " + words[next_hour];
        } else {
            return words[minutes_to] + " minutes to " + words[next_hour];
        }
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string h_temp;
    getline(cin, h_temp);

    int h = stoi(ltrim(rtrim(h_temp)));

    string m_temp;
    getline(cin, m_temp);

    int m = stoi(ltrim(rtrim(m_temp)));

    string result = timeInWords(h, m);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
