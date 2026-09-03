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

const int MaxN = 3e6 + 1;
bool isPrime[MaxN];

void sieve() {
    memset(isPrime, true, sizeof(isPrime));
   
    isPrime[0] = false;
    isPrime[1] = false;

    for(int i=2; i*i<=MaxN; i++) {
        if (!isPrime[i]) continue;
        for(int j=i*i; j<=MaxN; j+=i) {
            isPrime[j] = false;
        }
    }
}

int getSum(int n) {
    int s=0;
    while(n > 0) {
        s += n % 10;
        n /= 10;
    }
    return s;
}

void solve() {
    sieve();
    int L, R; cin >> L >> R;
    int ans = 0;
    FOR(x,L,R) {
        if (isPrime[x] && getSum(x) % 5 == 0) ans++;
    }
    cout << ans;
}

#undef int
int main() {
    init();
    solve();
}