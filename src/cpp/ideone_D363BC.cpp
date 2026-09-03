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
int a[MaxN + 1];
int pre[MaxN + 1];
int R[MaxN + 1];

int querySum(int L, int R) {
    return pre[R] - pre[L - 1];
}

void solve() {
    stack<int> st;
    int N, Q; cin >> N >> Q;
    FOR(i, 1, N) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    FOR(i, 1, N) {
        while(!st.empty() && a[st.top()] < a[i]) {
            R[st.top()] = i;
            st.pop(); 
        }
        st.push(i);
    }

    int u, v;
    while(Q--) {
        cin >> u >> v;
        int ans = 0;
        while(u < v) {
            if (R[u] == 0) {
                int r = min(N, v);
                int l = u + 1;
                ans += a[u] * (r - l + 1) - querySum(l, r);
                break;
            }

            int r = min(R[u] - 1, v);
            int l = u + 1;
            ans += a[u] * (r - l + 1) - querySum(l, r);
            u = R[u];
        }

        cout << ans << '\n';
    }
}

/** This is the end of my solution **/
 
#undef int
int main(void) {
    init();
    solve();
    return 0;
}