#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define int ll
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
#define REP(i, r) for(int i=0;i<(r);i++)
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>
#define ite std::vector<int>::iterator

template <class T> bool minimize(T& x,T y) {
    if (x > y) x = y; else return 0; return 1;
}
 
template <class T> bool maximize(T& x,T y) {
    if (x < y) x = y; else return 0; return 1;
}


const int MAX = 100000;

struct Disk {
    int inner, outer, height;
    Disk(int i=0, int o=0, int h=0) : inner(i), outer(o), height(h) {}
    bool operator<(const Disk& other) const {
        if (this->outer == other.outer) return this->inner > other.inner;
        return this->outer > other.outer;
    }
};

Disk disk[MAX + 1];
int dp[MAX + 1];

struct BIT {
    int n;
    vector<int> f;
    BIT(int n_) : n(n_), f(n + 1, 0) {}

    void update(int i, int x) {
        for(; i<=n; i += i & -i) maximize(f[i], x);
    }
    int getMax(int i) {
        int ans = 0;
        for(; i>=1; i -= i & -i) maximize(ans, f[i]);
        return ans;
    }
};
    
vector<int> compresed;

int getPos(int x) {
    return lower_bound(all(compresed), x) - compresed.begin() + 1;
}

void solve() {
    int n; cin >> n;
    FOR(i, 1, n) {
        cin >> disk[i].inner >> disk[i].outer >> disk[i].height;
        compresed.push_back(disk[i].inner);
    }
    sort(disk + 1, disk + n + 1);

    sort(all(compresed));
    compresed.erase(unique(all(compresed)), compresed.end());

    int ans = 0;
    BIT bit = BIT((int)compresed.size());
    FOR(i, 1, n) {
        int dpj = bit.getMax(getPos(disk[i].outer) - 1);
        dp[i] = max(disk[i].height, dpj + disk[i].height);
        bit.update(getPos(disk[i].inner), dp[i]);
        ans = max(ans, dp[i]);
    }
    cout << ans;
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