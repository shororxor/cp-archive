// #cpp | #codechef | #trie #binary_search
// Alice and Bob play Contact
// https://www.codechef.com/practice/course/icpc/ICPCTR14/problems/CHN16I

#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define mask(i) (1 << (i))
#define bit(x, i) (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcount(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin() + 1, v.end()
#define sz(v) (int)v.size()
#define sqr(x) ((x) * (x))
#define FOR(i, l, r) for (int i = (l); i <= (r); i++)
#define FORD(i, l, r) for (int i = (l); i >= (r); i--)
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int, int>
#define complex complex<long double>
#define ite std::vector<int>::iterator
#define next __next

template <class T> bool minimize(T &x, T y) {
    if (x > y)
        x = y;
    else
        return 0;
    return 1;
}

template <class T> bool maximize(T &x, T y) {
    if (x < y)
        x = y;
    else
        return 0;
    return 1;
}

const int ALPHABET_SIZE = 26;
const int MAX_NODES = 1e6;
const int MAX_WORDS = 1e5;

struct Node {
    int cnt;
    Node *child[ALPHABET_SIZE];
    Node() { reset(); }
    inline void reset() {
        cnt = 0;
        fill(child, child + ALPHABET_SIZE, nullptr);
    }
};

int trieNodeCount = 0;
string words[MAX_WORDS + 1];
Node nodes[MAX_NODES + 1];
Node *root;

int n, m;

Node *createNode() { return &nodes[trieNodeCount++]; }

void addString(const string &s) {
    Node *cur = root;
    for (auto &ch : s) {
        int c = ch - 'a';
        if (!cur->child[c])
            cur->child[c] = createNode();
        cur = cur->child[c];
        cur->cnt++;
    }
}

int search(const string &s) {
    Node *cur = root;
    vector<int> fre;
    for (auto &ch : s) {
        int c = ch - 'a';
        if (!cur->child[c])
            break;
        fre.push_back(cur->child[c]->cnt);
        cur = cur->child[c];
    }

    if (!sz(fre))
        return 0;
    int x = 1;
    int ans = 0;

    FORD(i, sz(fre) - 1, 0) {
        if (fre[i] >= x) {
            x++;
            ans++;
        }
    }
    return ans;
}

void solve() {
    trieNodeCount = 0;
    root = createNode();
    string s;
    FOR(i, 1, n) cin >> words[i];
    FOR(i, 1, m) {
        cin >> s;
        addString(s);
    }

    int ans = 0;
    FOR(i, 1, n) ans += search(words[i]);
    printf("%d\n", ans);

    FOR(i, 0, trieNodeCount - 1) nodes[i].reset();
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (cin >> n >> m)
        solve();
    return 0;
}
