#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'surfaceArea' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY A as parameter.
 */

int surfaceArea(vector<vector<int>> A) {
    int H = A.size();    // Rows of the grid
    int W = A[0].size(); // Columns of the grid

    int totalSurfaceArea = 0;

    // Loop through each cell in the grid
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            // Current height of the stack
            int height = A[i][j];

            // If the height is 0, it has no surface area.
            if (height > 0) {
                // Top and bottom surface area
                totalSurfaceArea += 2;

                // Calculate exposed sides:
                // - Compare with the cell above, or assume 0 if on the boundary
                totalSurfaceArea += (i == 0) ? height : max(0, height - A[i - 1][j]);

                // - Compare with the cell below, or assume 0 if on the boundary
                totalSurfaceArea += (i == H - 1) ? height : max(0, height - A[i + 1][j]);

                // - Compare with the cell to the left, or assume 0 if on the boundary
                totalSurfaceArea += (j == 0) ? height : max(0, height - A[i][j - 1]);

                // - Compare with the cell to the right, or assume 0 if on the boundary
                totalSurfaceArea += (j == W - 1) ? height : max(0, height - A[i][j + 1]);
            }
        }
    }

    return totalSurfaceArea;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int H = stoi(first_multiple_input[0]);

    int W = stoi(first_multiple_input[1]);

    vector<vector<int>> A(H);

    for (int i = 0; i < H; i++) {
        A[i].resize(W);

        string A_row_temp_temp;
        getline(cin, A_row_temp_temp);

        vector<string> A_row_temp = split(rtrim(A_row_temp_temp));

        for (int j = 0; j < W; j++) {
            int A_row_item = stoi(A_row_temp[j]);

            A[i][j] = A_row_item;
        }
    }

    int result = surfaceArea(A);

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
