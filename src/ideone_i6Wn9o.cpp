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
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define REPD(i,l,r) for(int i=(l);i>(r);i--)
#define complex complex<long double>
#define pii pair<int, int>
#define piii pair<pii, int>
#define vi vector<int>
#define vii vector<vi>
#define viii vector<vii>

const int neginf = -1e9-1;
const int posinf = 1e9+1;;
const int mod = 1000000007;
const double pi = 3.14159265359;
 
template <class T> bool minimize(T &x,T y) {
    if (x>y) x=y; else return 0; return 1;
}
 
template <class T> bool maximize(T &x,T y) {
    if (x<y) x=y; else return 0; return 1;
}
 
/** This is the end of my template **/

const int MaxN = 5e5;
const int MaxLog = 19;

int a[MaxN + 1];
int LOG2[MaxN + 1];
int dpMin[MaxN + 1][MaxLog + 1];
int dpGCD[MaxN + 1][MaxLog + 1];

void prepare() {
    LOG2[1] = 0;
    FOR(i, 2, MaxN) LOG2[i] = LOG2[i / 2] + 1;
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int getGCD(int L, int R) {
    int k = LOG2[R - L + 1];
    return min(dpMin[L][k], dpMin[R - (1 << k) + 1][k]);
}

int getMin(int L, int R) {
    int k = LOG2[R - L + 1];
    return gcd(dpGCD[L][k], dpGCD[R - (1 << k) + 1][k]);
}

pair<vector<int>,int> check(int N, int K) {
    vector<int> pos;
    bool flag = false;
    FOR(L, 1, N - K + 1) {
        int R = L + K - 1;
        if (getGCD(L,R) == getMin(L,R)) {
            pos.push_back(L);
            if (!flag) flag = true;
        }
    }
    return {pos, flag};
}

void solve() {
    int N; cin >> N;
    FOR(i, 1, N) {
        cin >> a[i];
        dpMin[i][0] = a[i];
        dpGCD[i][0] = a[i];
    }

    // process
    FOR(j, 1, LOG2[N]) {
        FOR(i, 1, N - (1 << j) + 1) {
            dpMin[i][j] = min(dpMin[i][j - 1], dpMin[i + (1 << (j - 1))][j - 1]);
            dpGCD[i][j] = gcd(dpGCD[i][j - 1], dpGCD[i + (1 << (j - 1))][j - 1]);
        }
    }

    // binary search
    int L = 1, R = N;
    int len = -1;
    vector<int> ans;

    while(L <= R) {
        int M = (L + R) >> 1;
        pair<vector<int>,int> res = check(N, M);
        if (res.second) {
            L = M + 1;
            len = M;
            ans = res.first;
        }
        else R = M - 1;
    }

    printf("%lld %lld\n", (int)ans.size(), len - 1);
    for(int& x : ans) printf("%lld ", x);
}

/** This is the end of my solution **/
 
#undef int
int main(void) {
    init();
    prepare();
    solve();
    return 0;
}