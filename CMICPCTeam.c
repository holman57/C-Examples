#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'acmTeam' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts STRING_ARRAY topic as parameter.
 */

#include <bits/stdc++.h>

using namespace std;

vector<int> acmTeam(vector<string> topic) {
    int maxTopics = 0;  // Maximum topics known by any team
    int teamCount = 0;  // Count of teams knowing maxTopics

    // Number of people in the group
    int n = topic.size();

    // Compare every pair of people (i, j)
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Combine their knowledge using bitwise OR
            int combinedTopics = 0;
            for (size_t k = 0; k < topic[i].size(); ++k) {
                if (topic[i][k] == '1' || topic[j][k] == '1') {
                    combinedTopics++;
                }
            }

            // Update maxTopics and teamCount
            if (combinedTopics > maxTopics) {
                maxTopics = combinedTopics;
                teamCount = 1;
            } else if (combinedTopics == maxTopics) {
                teamCount++;
            }
        }
    }

    return {maxTopics, teamCount};
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<string> topic(n);

    for (int i = 0; i < n; i++) {
        string topic_item;
        getline(cin, topic_item);

        topic[i] = topic_item;
    }

    vector<int> result = acmTeam(topic);

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
