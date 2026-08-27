#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

class DPDEBUGGER 
{
private:
    FILE* fout;

public:
    DPDEBUGGER(const char* name) {
        fout = fopen(name, "w");
    }
    ~DPDEBUGGER() {
        if (fout) fclose(fout);
    }

public:
    inline void start_dot_graph() {
        fprintf(fout, "digraph DP {\n");
        fprintf(fout, "node [shape=ellipse];\n");
        fprintf(fout, "ranksep=2.0;\n");
        fprintf(fout, "nodesep=0.8;\n");
    }

    inline void end_dot_graph() {
        fprintf(fout, "}\n");
    }

    // dp bitmask debug with option chooose or not choose
    inline void log_edge(int i, int m1, int j, int m2, int val1, int val2, bool used) {
        const char* color = used ? "red" : "black";
        fprintf(fout, "\"(%d,%d)\" [label=\"(%d,%d)\\nvalue=%d\"];\n", i, m1, i, m1, val1);
        fprintf(fout, "\"(%d,%d)\" [label=\"(%d,%d)\\nvalue=%d\"];\n", j, m2, j, m2, val2);
        fprintf(fout, "\"(%d,%d)\" -> \"(%d,%d)\" [color=%s];\n", i, m1, j, m2, color);
    }

    // add other dp type problem with different states
};

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
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define REPD(i,l,r) for(int i=(l);i>(r);i--)
#define BITSET(size, x) std::bitset<size>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>

const int posinf = 1e9;
const int neginf = -1e9;
const int mod = 1000000007;
const double pi = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

/** This is the end of my template **/

const int MAX = 51;
bool isPrime[MAX + 1];
int A[MAX + 1];
int dp[MAX + 1][1 << 15];
int new_dp[1 << 15];
int mask[MAX + 1];

vector<int> primes;

void sieve() {
    fill(isPrime, isPrime + MAX + 1, true);
    isPrime[0] = isPrime[1] = false;
    for(int i=2; i <= MAX; i++) {
        if (!isPrime[i]) continue;
        primes.push_back(i);
        for(int j=i*i; j <= MAX; j += i) {
            isPrime[j] = false;
        }
    }
}

int compute_mask(int x) {
    int id = 0;
    int mask = 0;
    for(int& p : primes) {
        if (x % p == 0) mask |= (1 << id);
        id++;
    }
    return mask;
}

DPDEBUGGER DB = DPDEBUGGER("dp_backward.dot");

void solve() {
    int N; cin >> N;
    FOR(i, 1, N) {
        cin >> A[i];
        mask[i] = compute_mask(A[i]);
    }
    
    memset(dp, 0, sizeof(dp));

    FOR(i, 1, N) {
        FOR(mask, 0, (1 << 15) - 1) {
            maximize(dp[i + 1][mask], dp[i][mask]);

            if (!(mask & ::mask[i])) {
                int new_mask = (mask | ::mask[i]);
                maximize(dp[i + 1][new_mask], dp[i][mask] + 1);
            }
        }
    }

    int ans = 0;
    FOR(state, 0, (1 << 15) - 1) maximize(ans, dp[N + 1][state]);
    cout << ans << '\n';
}

/** This is the end of my solution **/

#undef int
int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    sieve();
    int T; cin >> T;
    while(T--) solve();
}