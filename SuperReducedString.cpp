#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'superReducedString' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string superReducedString(string s) {
    // Using a stack to perform the reduction
    stack<char> st;

    for (char ch : s) {
        if (!st.empty() && st.top() == ch) {
            // If the top of the stack is the same as the current character, pop the stack
            st.pop();
        } else {
            // Otherwise, push the current character onto the stack
            st.push(ch);
        }
    }

    // Reconstruct the reduced string from the stack
    string result = "";
    while (!st.empty()) {
        result = st.top() + result; // Add characters in reverse order
        st.pop();
    }

    // If the resultant string is empty, return "Empty String"
    return result.empty() ? "Empty String" : result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = superReducedString(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
