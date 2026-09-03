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
#define mask(i) (1LL << (i))
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcount(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sz(v) (int)v.size();
#define sqr(x) ((x) * (x))
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

const int MaxN = 1e6+1;
int divisor[MaxN]; // return number of divisors for input n
 
/*
1 2 3 4 5 6 7 8 9 10 11 12
1 2 2 3 2 4 2 4 3 4  2  6
*/
 
void prepare() {
    divisor[1] = 1;
    FOR(i,2,MaxN) divisor[i] = 2;
    for(int i=2; i*2 <= MaxN; i++) {
        for(int j=i*2; j<=MaxN; j+=i) {
            divisor[j]++;
        }
    }
}
 
void solve() {
    prepare();
    int n; cin >> n;
    int x;
    FOR(i,1,n) {
        cin >> x;
        cout << divisor[x] << '\n';
    }
}
#undef int
int main() {
    init();
    solve();
}