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

enum class State {
    Default = 0,
    Win = 1,
    Lose = 2
};

string convert(State& state) {
    switch(state) {
        case State::Default : return "Default"; 
        case State::Win : return "Win";
        case State::Lose: return "Lose";
    }
    return "Undefined";
}

const int MAXK = 100;
const int MAXL = 100;
const int MAXH = 10000;

State state[MAXH + 1];
int g[MAXH + 1];
int moves[MAXK + 1];
int heaps[MAXL + 1];

int k, m, l;

int getMex(vector<int>& Q) {
    int res = 0;
    sort(Q.begin(), Q.end());
    for(int& q : Q) if (res == q) ++res;
    return res;
}

// dp bottom up
void computeGrundy() {
    g[0] = 0;
    FOR(i, 1, MAXH) {
        vector<int> Q;
        FOR(j, 1, k) if (i - moves[j] >= 0) Q.push_back(g[i - moves[j]]);
        g[i] = getMex(Q);
    }
}


// dp topdown
int getValue(int u) {
    if (u == 0) return g[u] = 0;
    if (g[u] != -1) return g[u];

    vector<int> Q;
    FOR(i, 1, k) if (u - moves[i] >= 0) Q.push_back(getValue(u - moves[i]));
    return g[u] = getMex(Q);
}

bool nimGame() {
    int nim = 0;
    FOR(i, 1, l) nim ^= g[heaps[i]];
    return nim != 0;
}

void solve() {
    cin >> k;
    FOR(i, 1, k) cin >> moves[i];

    fill(g, g + MAXH + 1, -1); // dp topdown need this line
    FOR(i, 0, MAXH) getValue(i);

    cin >> m;
    FOR(i, 1, m) {
        cin >> l;
        FOR(i, 1, l) cin >> heaps[i];
        if (nimGame()) cout << "W";
        else cout << "L";
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