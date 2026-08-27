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

// a state is called win if it can reach to at least a lose state
enum class State {
    Default = 0,
    Win = 1,
    Lose = 2
};

const int MAX = 1000;
State dp[MAX];

State getState(int u) {
    if (dp[u] != State::Default) return dp[u];
    if (u == 0) return dp[u] = State::Lose;

    // for valid move (u, v) in Q
    FORD(v, u - 1, max(u - 3, 0)) {
        if (getState(v) == State::Lose) 
            return dp[u] = State::Win;
    }

    return dp[u] = State::Lose;
}

void solve() {
    getState(100);
    FOR(i, 1, 100) {
        if (dp[i] == State::Win) printf("i = %d | win\n", i);
        else printf("i = %d | lose\n", i);
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