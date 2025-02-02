#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'bomberMan' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING_ARRAY grid
 */

vector<string> detonate(const vector<string> &grid, int r, int c) {
    vector<string> result(r, string(c, 'O')); // Assume all are bombs
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 'O') {
                result[i][j] = '.'; // Detonate current bomb
                if (i > 0) result[i - 1][j] = '.'; // Above
                if (i < r - 1) result[i + 1][j] = '.'; // Below
                if (j > 0) result[i][j - 1] = '.'; // Left
                if (j < c - 1) result[i][j + 1] = '.'; // Right
            }
        }
    }
    return result;
}

vector<string> bomberMan(int n, vector<string> grid) {
    if (n == 1) {
        // Initial state remains for n = 1
        return grid;
    }

    int r = grid.size();
    int c = grid[0].size();

    if (n % 2 == 0) {
        // All cells turn into bombs for even seconds
        return vector<string>(r, string(c, 'O'));
    }

    // Simulate bomb detonation for n = 3
    vector<string> gridAfter3 = detonate(grid, r, c);

    if (n % 4 == 3) {
        // Pattern repeats at n = 3
        return gridAfter3;
    }

    // Simulate bomb detonation for n = 5
    vector<string> gridAfter5 = detonate(gridAfter3, r, c);

    // Pattern repeats at n = 5 (n % 4 = 1)
    return gridAfter5;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int r = stoi(first_multiple_input[0]);

    int c = stoi(first_multiple_input[1]);

    int n = stoi(first_multiple_input[2]);

    vector<string> grid(r);

    for (int i = 0; i < r; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    vector<string> result = bomberMan(n, grid);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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

vector<string> split(const string &str) {
vector<string> tokens;

string::size_type start = 0;
string::size_type end = 0;

while ((end = str.find(" ", start)) != string::npos) {
tokens.push_back(str.substr(start, end - start));

start = end + 1;
}

tokens.push_back(str.substr(start));

return tokens;
}
