#include <bits/stdc++.h>

using namespace std;

map<int, string> intToString;
vector<string> order;
vector<string> input[1010];

struct Trie {
    Trie *next[1010];

    Trie() {
        for (int i = 0; i < 1010; ++i) next[i] = nullptr;
    }

    void insert(int *s) {
        if (*s == -1) return;
        int cur = *s;
        if (next[cur] == nullptr) next[cur] = new Trie();
        next[cur]->insert(s + 1);
    }

    void dfs(string hier) {
        for (int i = 0; i < 1010; ++i) {
            if (next[i] != nullptr) {
                cout << hier << intToString[i] << '\n';
                next[i]->dfs(hier + "--");
            }
        }
    }
};

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        while (m--) {
            string s;
            cin >> s;
            input[i].push_back(s);
            order.push_back(s);
        }
    }

    sort(order.begin(), order.end());
    order.erase(unique(order.begin(), order.end()), order.end());
    int cnt = 0;
    for (auto s : order) intToString[cnt++] = s;

    Trie *root = new Trie();
    for (int i = 0; i < n; ++i) {
        int in[30];
        memset((void *)in, -1, sizeof(in));
        for (int j = 0; j < input[i].size(); ++j)
            in[j] = (int)(lower_bound(order.begin(), order.end(), input[i][j]) - order.begin());
        root->insert(in);
    }

    root->dfs("");

    return 0;
}