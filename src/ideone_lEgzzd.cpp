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

void sieve(int n, vector<int>& primes) {
    vector<bool> isPrime(n+1, true);
    
    isPrime[0] = isPrime[1] = false;    

    for(int i=2; i*i<=n; i++) {
        if (!isPrime[i]) continue;
        for(int j=i*i; j<=n; j+=i) {
            isPrime[j] = false;
        }
    }
    FOR(i,2,n) if (isPrime[i]) primes.push_back(i);
}

void solve() {
    int L, R; cin >> L >> R;
    vector<bool> isPrime(R - L + 1, true);

    if (L == 1) isPrime[0] = false;

    vector<int> primes;
    sieve(sqrt(R), primes);

    for(int i : primes) {
        int pos = max(i * i, ((L + i - 1) / i) * i);
        for(int j = pos; j <= R; j += i) {
            isPrime[j - L] = false;
        }
    }

    int ans = 0;
    for(int i = 0; i <= R - L; i++) {
        if (isPrime[i]) ans++;
    }
    cout << ans << '\n';
}

#undef int
int main() {
    init();
    int T; cin >> T;
    while(T--) solve();
}