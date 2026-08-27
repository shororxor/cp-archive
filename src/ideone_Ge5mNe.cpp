#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define mask(i) (1 << (i))
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcount(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sz(v) (int)v.size()
#define sqr(x) ((x) * (x))
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>
#define ite std::vector<int>::iterator

const int POSINF = 1e9;
const int NEGINF = -1e9;
const int MOD = 1000000007;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

const int MAX = 100;
int c[MAX + 1];

void merge(ite i, ite n, ite j, ite m, ite k) {
    while(i < n && j < m) {
        *k++ = min(*i, *j);
        if (*i <= *j) i++;
        else j++;
    }

    while(i < n) *k++ = *i++;
    while(j < m) *k++ = *j++;
}

void mergeSort(ite l, ite r) {
    if (l >= r) return;

    ite m = l + (r - l) / 2;
    mergeSort(l, m);
    mergeSort(m + 1, r);

    merge(l, m + 1, m + 1, r + 1, c);
    copy(c, c + (r - l + 1), l);
}

inline void solve() {
    int n; cin >> n;
    vector<int> a(n, 0);
    FOR(i, 0, n - 1) cin >> a[i];
    mergeSort(a.begin(), a.end() - 1);
    for(auto& x : a) cout << x << ' ';
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
}