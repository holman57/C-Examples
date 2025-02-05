#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'twoPluses' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING_ARRAY grid as parameter.
 */

int twoPluses(vector<string> grid) {
    int n = grid.size();    // Rows
    int m = grid[0].size(); // Columns

    // Helper function to calculate the size of the "plus" at (x, y)
    auto calculatePlus = [&](int x, int y) {
        int size = 0;
        while (x - size >= 0 && x + size < n && y - size >= 0 && y + size < m &&
               grid[x - size][y] == 'G' && grid[x + size][y] == 'G' &&
               grid[x][y - size] == 'G' && grid[x][y + size] == 'G') {
            size++; // Increase size while it is still valid
        }
        return size - 1; // Largest valid "plus" size
    };

    // Store all valid "pluses" as {centerX, centerY, maxArmLength}
    vector<tuple<int, int, int>> pluses;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'G') {
                int maxSize = calculatePlus(i, j);
                for (int s = 0; s <= maxSize; s++) {
                    pluses.emplace_back(i, j, s);
                }
            }
        }
    }

    // Function to mark the cells covered by a "plus"
    auto markCells = [&](int x, int y, int size) {
        set<pair<int, int>> cells;
        cells.insert({x, y});
        for (int i = 1; i <= size; i++) {
            cells.insert({x - i, y});
            cells.insert({x + i, y});
            cells.insert({x, y - i});
            cells.insert({x, y + i});
        }
        return cells;
    };

    // Find the maximum product of two non-overlapping "pluses"
    int maxProduct = 0;
    for (size_t i = 0; i < pluses.size(); i++) {
        for (size_t j = i + 1; j < pluses.size(); j++) {
            int x1, y1, size1;
            int x2, y2, size2;
            tie(x1, y1, size1) = pluses[i];
            tie(x2, y2, size2) = pluses[j];

            // Get cells covered by both pluses
            auto cells1 = markCells(x1, y1, size1);
            auto cells2 = markCells(x2, y2, size2);

            // Check for overlap
            bool overlap = false;
            for (const auto &cell : cells1) {
                if (cells2.count(cell)) {
                    overlap = true;
                    break;
                }
            }

            // If no overlap, calculate product of sizes
            if (!overlap) {
                int area1 = 4 * size1 + 1;
                int area2 = 4 * size2 + 1;
                maxProduct = max(maxProduct, area1 * area2);
            }
        }
    }

    return maxProduct;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    int result = twoPluses(grid);

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
