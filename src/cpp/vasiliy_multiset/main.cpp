// #cpp | #codeforces | #bitwise_operation #trie
// D. Vasiliy's Multiset
// https://codeforces.com/problemset/problem/706/D

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
    if (x > y) x = y;
    else return 0;
    return 1;
}

template <class T> bool maximize(T &x, T y) {
    if (x < y) x = y;
    else return 0;
    return 1;
}

struct Node {
    int cnt;
    Node *child[2];
    Node() {
        cnt = 0;
        fill(child, child + 2, nullptr);
    }
};

Node *root;

Node *createNode() {
    return new Node();
}

void addVal(int x) {
    Node *cur = root;
    FORD(i, 30, 0) {
        int j = ((x >> i) & 1);
        if (!cur->child[j]) cur->child[j] = createNode();
        cur = cur->child[j];
        cur->cnt++;
    }
}

void removeVal(int x) {
    Node *cur = root;
    FORD(i, 30, 0) {
        int j = ((x >> i) & 1);
        cur = cur->child[j];
        cur->cnt--;
    }
}

int queryVal(int x) {
    Node *cur = root;
    int ans = 0;
    FORD(i, 30, 0) {
        int k = ((x >> i) & 1);
        if (k == 0) {
            if (cur->child[1] && cur->child[1]->cnt) {
                cur = cur->child[1];
                ans += (1 << i);
            }
            else cur = cur->child[0];
        }
        else if (k == 1) {
            if (cur->child[0] && cur->child[0]->cnt) {
                cur = cur->child[0];
                ans += (1 << i);
            }
            else cur = cur->child[1];
        }
    }
    return ans;
}

void solve() {
    root = createNode();
    int q;
    cin >> q;
    char t;
    int x;
    addVal(0);
    while (q--) {
        cin >> t >> x;
        if (t == '+') addVal(x);
        else if (t == '-') removeVal(x);
        else printf("%d\n", queryVal(x));
    }
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
    return 0;
}
