#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'matrixRotation' function below.
 *
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY matrix
 *  2. INTEGER r
 */

void matrixRotation(vector<vector<int>> matrix, int r) {
    int m = matrix.size();    // Rows
    int n = matrix[0].size(); // Columns

    // Determine the number of layers to process
    int num_layers = min(m, n) / 2;

    // Create the rotated matrix to store the result
    vector<vector<int>> result = matrix;

    for (int layer = 0; layer < num_layers; layer++) {
        // Extract the current layer into a 1D array
        vector<int> elements;

        // Top row
        for (int j = layer; j < n - layer; j++) {
            elements.push_back(matrix[layer][j]);
        }
        // Right column
        for (int i = layer + 1; i < m - layer; i++) {
            elements.push_back(matrix[i][n - layer - 1]);
        }
        // Bottom row (reversed)
        for (int j = n - layer - 2; j >= layer; j--) {
            elements.push_back(matrix[m - layer - 1][j]);
        }
        // Left column (reversed)
        for (int i = m - layer - 2; i > layer; i--) {
            elements.push_back(matrix[i][layer]);
        }

        // Perform the rotation
        int layer_size = elements.size();
        int r_eff = r % layer_size; // Effective rotations

        // Create a rotated 1D array
        vector<int> rotated_layer(layer_size);
        for (int i = 0; i < layer_size; i++) {
            rotated_layer[i] = elements[(i + r_eff) % layer_size];
        }

        // Place rotated elements back into the correct positions
        int idx = 0;

        // Top row
        for (int j = layer; j < n - layer; j++) {
            result[layer][j] = rotated_layer[idx++];
        }
        // Right column
        for (int i = layer + 1; i < m - layer; i++) {
            result[i][n - layer - 1] = rotated_layer[idx++];
        }
        // Bottom row
        for (int j = n - layer - 2; j >= layer; j--) {
            result[m - layer - 1][j] = rotated_layer[idx++];
        }
        // Left column
        for (int i = m - layer - 2; i > layer; i--) {
            result[i][layer] = rotated_layer[idx++];
        }
    }

    // Print the resulting matrix
    for (auto row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int m = stoi(first_multiple_input[0]);

    int n = stoi(first_multiple_input[1]);

    int r = stoi(first_multiple_input[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

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
