#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'biggerIsGreater' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING w as parameter.
 */

string biggerIsGreater(string w) {
    int n = w.size();

    // Step 1: Find the pivot
    int i = n - 2;
    while (i >= 0 && w[i] >= w[i + 1]) {
        i--;
    }

    // If no pivot is found, return "no answer"
    if (i < 0) {
        return "no answer";
    }

    // Step 2: Find the successor
    int j = n - 1;
    while (j > i && w[j] <= w[i]) {
        j--;
    }

    // Step 3: Swap pivot with successor
    swap(w[i], w[j]);

    // Step 4: Reverse the suffix
    reverse(w.begin() + i + 1, w.end());

    return w;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string T_temp;
    getline(cin, T_temp);

    int T = stoi(ltrim(rtrim(T_temp)));

    for (int T_itr = 0; T_itr < T; T_itr++) {
        string w;
        getline(cin, w);

        string result = biggerIsGreater(w);

        fout << result << "\n";
    }

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
