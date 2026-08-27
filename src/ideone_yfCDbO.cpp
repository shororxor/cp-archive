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
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define REPD(i,l,r) for(int i=(l);i>(r);i--)
#define BITSET(size, x) std::bitset<size>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>

const int POSINF = 1e9;
const int NEFINF = -1e9;
const int MOD = 1000000007;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

/** This is the end of my template **/
#define data pair<ll, pair<int,int>>

const int MaxN = 1e5;
int a[MaxN + 1];
set<pair<int,int>> visited;

inline void solve() {
    int n, k; cin >> n >> k;
    FOR(i, 1, n) cin >> a[i];
    sort(a + 1, a + n + 1);

    priority_queue<data, vector<data>, greater<data>> pq;
    pq.push({1LL * a[1] * a[2], {1, 2}});
    visited.insert({1, 2});
    int t = 0;

    while(!pq.empty()){
        data top = pq.top();
        int idx1 = top.second.first;
        int idx2 = top.second.second;
        pq.pop();
        t++;

        if (t == k) {
           cout << top.first << '\n';
           break;
        }

        if (idx2 + 1 <= n && !visited.count({idx1, idx2 + 1})) {
            pq.push({1LL * a[idx1] * a[idx2  + 1], {idx1, idx2 + 1}});
            visited.insert({idx1, idx2 + 1});
        }

        if (idx1 + 1 < idx2 && !visited.count({idx1 + 1, idx2})) {
            pq.push({1LL * a[idx1 + 1] * a[idx2], {idx1 + 1, idx2}});
            visited.insert({idx1 + 1, idx2});
        }
    }
}

/** This is the end of my solution **/

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}