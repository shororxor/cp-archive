// #cpp | #z_function

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
#define REP(i, r) for (int i = 0; i < r; i++)
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int, int>
#define complex complex<long double>
#define ite std::vector<int>::iterator

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

const int MAX = 100;

int lenStr;
int z[MAX];
char str[MAX];

void solve() {
    scanf("%s", str + 1);
    lenStr = strlen(str + 1);

    for (int i = 2, l = 0, r = 0; i <= lenStr; i++) {
        if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        while (i + z[i] - 1 < lenStr && str[1 + z[i]] == str[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }

    FOR(i, 1, lenStr) cout << z[i] << ' ';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
    return 0;
}
