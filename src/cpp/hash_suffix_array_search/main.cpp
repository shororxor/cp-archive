// #cpp | #vnoj | #hashing #binary_search #string #suffix_array

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

struct SA {
    int pre, left, right;
    SA(int pre_ = 0, int left_ = 0, int right_ = 0) {
        this->pre = pre_;
        this->left = left_;
        this->right = right_;
    }
};

namespace SuffixArray {
const int MAX = 1000;

int index, k;
SA p[MAX];
int c[MAX];
int lenStr;
char str[MAX];

bool cmpInit(const SA &p1, const SA &p2) {
    return str[p1.pre] < str[p2.pre];
}

bool cmpNext(const SA &p1, const SA &p2) {
    return (p1.left == p2.left ? p1.right < p2.right : p1.left < p2.left);
}

void output() {
    FOR(i, 1, lenStr)
    printf("p[%d] = (%d, %d, %d) | c[%d] = %d\n", i, p[i].pre, p[i].left, p[i].right, p[i].pre, c[p[i].pre]);
    printf("\n");
}

void process() {
    FOR(i, 1, lenStr) p[i].pre = i;
    stable_sort(p + 1, p + lenStr + 1, cmpInit);
    c[p[1].pre] = index = 1;
    FOR(i, 2, lenStr)
    c[p[i].pre] = str[p[i - 1].pre] == str[p[i].pre] ? index : ++index;
    output();

    k = 1;
    while ((1 << k++) <= lenStr) {
        if (index == lenStr) break;
        FOR(i, 1, lenStr)
        p[i].left = c[p[i].pre], p[i].right = c[(p[i].pre + ((1 << k) >> 1) - 1) % lenStr + 1];
        stable_sort(p + 1, p + lenStr + 1, cmpNext);
        c[p[1].pre] = index = 1;
        FOR(i, 2, lenStr)
        c[p[i].pre] = p[i - 1].left == p[i].left && p[i - 1].right == p[i].right ? index : ++index;
        SuffixArray::output();
    }
}

void init() {
    scanf("%s", str + 1);
    lenStr = strlen(str + 1);
}
} // namespace SuffixArray

void solve() {
    SuffixArray::init();
    SuffixArray::process();
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
