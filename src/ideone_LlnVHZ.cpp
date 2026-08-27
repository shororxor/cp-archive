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
int products[MaxN + 1];
pii dp[MaxN + 1][MaxLog + 1];

void prepare() {
    LOG2[1] = 0;
    FOR(i, 2, MaxN) LOG2[i] = LOG2[i / 2] + 1;
}

pii getMin(int L, int R) {
    int min_element = posinf;
    int index = -1;

    while(L <= R) {
        int k = LOG2[R - L + 1];
        if (dp[L][k].first < min_element) {
            min_element = dp[L][k].first;
            index = dp[L][k].second;
        }
        L += (1 << k);
    }
    return {min_element, index};
}

int findPos(int T, int L, int R) {
    auto [min_element, index] = getMin(L, R);
    if (min_element > T) return R + 1;

    if (min_element == 0) {
        int left = findPos(T, L, index - 1);
        int right = findPos(T, index + 1, R);
        if (left == index && right == R + 1) return R + 1;
        else if (left < index) return left;
        else if (right < R + 1) return right;
    }

    while(L <= R && min_element <= T) {
        R = index - 1;
        if (R < L) break;

        auto tmp = getMin(L, R);
        min_element = tmp.first;
        index = tmp.second;

        if (min_element == 0) {
            int left = findPos(T, L, index - 1);
            int right = findPos(T, index + 1, R);
            if (left == index && right == R + 1) break;
            else if (left < index) return left;
            else if (right < R + 1) return right;
        }
    }

    return R + 1; // the previous index
}

void solve() {
    int N, M; cin >> N >> M;
    FOR(i, 1, N) {
        cin >> products[i];
        dp[i][0].first = products[i];
        dp[i][0].second = i;
    }

    // process
    FOR(j, 1, LOG2[N]) {
        FOR(i, 1, N - (1 << j) + 1) {
            if (dp[i][j - 1].first < dp[i + (1 << (j - 1))][j - 1].first) {
                dp[i][j].first = dp[i][j - 1].first;
                dp[i][j].second = dp[i][j - 1].second;
            }
            else {
                dp[i][j].first = dp[i + (1 << (j - 1))][j - 1].first;
                dp[i][j].second = dp[i + (1 << (j - 1))][j - 1].second;
            }
        }
    }

    // query
    int T, L, R;
    FOR(i, 1, M) {
        cin >> T >> L >> R;
        while(L <= R) {
            L = findPos(T, L, R);
            if (L > R) break; // return R + 1 (no elements <= T)

            T = T % products[L++];
            if (T == 0) break;
        }

        printf("%lld\n", T);
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