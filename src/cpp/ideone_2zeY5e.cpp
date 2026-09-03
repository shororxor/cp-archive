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

const int MaxN = 2e5;
const int MaxLog = 17;

int LOG2[MaxN + 1];
int par[MaxN + 1][MaxLog + 1];
vector<int> tree[MaxN + 1];

int N, Q;

void prepare() {
    LOG2[1] = 0;
    FOR(i, 2, MaxN) LOG2[i] = LOG2[i / 2] + 1;
}

void DFS(int u) {
    for(int& v : tree[u]) {
        if (v != par[u][0]) {
            par[v][0] = u; 
            FOR(j, 1, LOG2[N]) par[v][j] = par[par[v][j - 1]][j - 1];
            DFS(v);
        }
    }
}

void solve() {
    cin >> N >> Q;
    int u;
    FOR(v, 2, N) {
        cin >> u;
        tree[u].push_back(v); 
    }

    DFS(1);
    int x, k;
    while(Q--) {
        cin >> x >> k;
        FORD(j, LOG2[N], 0) {
            if (k & (1 << j)) {
                x = par[x][j];
            }
        }
        printf("%lld\n", x ? x : -1);
    }
}

/** This is the end of my solution **/
 
#undef int
int main(void) {
    init();
    prepare();
    solve();
    return 0;
}