#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;
 
void init() {
    #ifndef ONLINE_JUDGE
    if (!freopen("input.inp", "r", stdin)) {}
    if (!freopen("output.out", "w", stdout)) {}
    #endif
 
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
 
#define ll long long
#define int ll
#define mask(i) (1LL << (i))
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcountll(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sqr(x) ((x) * (x))
#define pii pair<int, int>
#define piii pair<pii, int>
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define REPD(i,l,r) for(int i=(l);i>(r);i--)
#define complex complex<long double>
 
const int neginf = INT_MIN;
const int posinf = INT_MAX;
const int mod = 1000000007;
const double pi = 3.14159265359;
 
template <class T> bool minimize(T &x,T y) {
    if (x>y) x=y; else return 0; return 1;
}
 
template <class T> bool maximize(T &x,T y) {
    if (x<y) x=y; else return 0; return 1;
}
 
/** This is the end of my template **/

const int MaxN = 30000;
int A[MaxN + 1];
int F[MaxN + 1];
int B[MaxN + 1];

void solve() {
    int N; cin >> N;
    FOR(i, 1, N) {
        cin >> A[i];
        B[i] = posinf;
    }

    B[0] = -1;
    int ans = 0;

    FOR(i, 1, N) {
        int Fj = lower_bound(B, B + i, A[i]) - B;
        Fj--;
        F[i] = Fj + 1;
        minimize(B[F[i]], A[i]);
        maximize(ans, F[i]);
    }

    printf("%lld\n", ans);
}

/** This is the end of my solution **/
 
#undef int
int main(void) {
    init();
    solve();
    return 0;
}