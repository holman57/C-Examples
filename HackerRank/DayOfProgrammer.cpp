#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

string dayOfProgrammer(int y) {
    int d = 13;
    if(!(y%4) && (y < 1918 || y%100 || !(y%400))) d--;
    if(y == 1918) d = 26;
    return to_string(d) + ".09." + to_string(y);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));
    string year_temp;
    getline(cin, year_temp);
    int year = stoi(ltrim(rtrim(year_temp)));
    string result = dayOfProgrammer(year);
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
