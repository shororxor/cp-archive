#include <bits/stdc++.h>
using namespace std;
    
void init() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin); 
    freopen("output.out", "w", stdout);
    #endif
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
    
#define ll long long
#define int ll
#define mask(i) (1LL << (i)) // 2^i
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcount(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sz(v) (int)v.size();
#define sqr(x) ((x) * (x))
#define pii pair<int, int>
#define piii pair<int, pii>
#define vi vector<int>
#define vii vector<vector<int>>
#define fi first
#define se second
#define pb push_back
#define pf push_front
#define mp make_pair
#define pq priority_queue
#define binary(x, n) (std::bitset<n>(x).to_string())
#define FOR(i,l,r) for(auto i=(l);i<=(r);i++)
#define REP(i,l,r) for(auto i=(l);i<(r);i++)
#define FORD(i,l,r) for(auto i=(l);i>=(r);i--)
#define REPD(i,l,r) for(auto i=(l);i>(r);i--)
const int inf = 1e9+1;
const int MOD = 1e9+7;
const double PI = 3.14159265359;
    
template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}
    
template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

int n, m; 

int F(int X)
{
    int cnt = 0;
    FOR(i,1,n) {
        cnt += min(m, X / i);
    }
    return cnt;
}

void solve()
{
    cin >> n >> m;
    int K; cin >> K;

    int L = 1;
    int R = n * m;

    int ans = 0;

    while(L <= R) {
        int M = (L + R) >> 1;
        if(F(M) >= K) {
            ans = M;
            R = M - 1;
        }
        else L = M + 1;
    }

    cout << ans;
}

#undef int
int main() {
    init();
    solve();
}