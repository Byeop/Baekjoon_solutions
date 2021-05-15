#include <bits/stdc++.h>

using namespace std;

int main(void) {
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 1; i <= n; ++i) {
        vector<string> st;
        string in, w;
        getline(cin, in);
        stringstream ss(in);
        while (getline(ss, w, ' ')) st.push_back(w);
        cout << "Case #" << i << ": ";
        while (!st.empty()) {
            cout << st.back() << " ";
            st.pop_back();
        }
        cout << "\n";
    }

    return 0;
}