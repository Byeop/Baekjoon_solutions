#include <bits/stdc++.h>

using namespace std;

int main(void) {
    string s;
    cin >> s;

    vector<char> st;
    for (auto c : s) {
        if (!st.empty() && c == ')' && st.back() == '(')
            st.pop_back();
        else
            st.push_back(c);
    }
    printf("%d", st.size());

    return 0;
}