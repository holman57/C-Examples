#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'alternate' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int alternate(string s) {
    // Get all unique characters present in the string
    unordered_set<char> unique_chars(s.begin(), s.end());
    vector<char> chars(unique_chars.begin(), unique_chars.end());

    int max_length = 0;

    // Consider all pairs of unique characters
    for (int i = 0; i < chars.size(); i++) {
        for (int j = i + 1; j < chars.size(); j++) {
            char ch1 = chars[i];
            char ch2 = chars[j];

            // Check if we can form an alternating string with ch1 and ch2
            string filtered;
            for (char c : s) {
                if (c == ch1 || c == ch2) {
                    filtered += c;
                }
            }

            // Validate if the filtered string alternates
            bool is_alternating = true;
            for (int k = 1; k < filtered.size(); k++) {
                if (filtered[k] == filtered[k - 1]) {
                    is_alternating = false;
                    break;
                }
            }

            // Update the maximum length if valid
            if (is_alternating) {
                max_length = max(max_length, (int)filtered.size());
            }
        }
    }

    return max_length;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string l_temp;
    getline(cin, l_temp);

    int l = stoi(ltrim(rtrim(l_temp)));

    string s;
    getline(cin, s);

    int result = alternate(s);

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
