#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define mask(i) (1 << (i))
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcount(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sz(v) (int)v.size()
#define sqr(x) ((x) * (x))
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define BITSET(size, x) std::bitset<size>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>

const int POSINF = 1e9;
const int NEFINF = -1e9;
const int MOD = 1000000007;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

inline vector<pii> factorization(int n) {
    vector<pii> ans;
    for(int i = 2; i * i <= n; i++) {
        int k = 0;
        if (n % i == 0) {
            while(n % i == 0) {
                k++;
                n /= i;
            }
            ans.push_back({i, k});
        }
    }
    if (n > 1) ans.push_back({n, 1});
    return ans;
}

void generate_divisors_exponents(const vi& max_exp, vector<vi>& result, vi current, int idx) {
    if (idx == (int)max_exp.size()) {
        result.push_back(current);
        return;
    }
    for (int i = 0; i <= max_exp[idx]; ++i) {
        current[idx] = i;
        generate_divisors_exponents(max_exp, result, current, idx + 1);
    }
}

inline int process() {
    int n, m; cin >> n >> m;
    if (n == m) return 0;
    if (n == 1 || n > m) return -1;

    vector<pii> np = factorization(n);
    vector<pii> mp = factorization(m);
    int k = np.size();

    if (sz(np) != sz(mp)) return -1;
    vi base(k), exp_n(k), exp_m(k);

    FOR(i, 0, k - 1) {
        if (np[i].first != mp[i].first) return -1;
        base[i] = np[i].first;
        exp_n[i] = np[i].second;
        exp_m[i] = mp[i].second;
    }

    // all divisor exponent vectors of n
    vector<vi> divisor_exponents;
    generate_divisors_exponents(exp_n, divisor_exponents, vi(k), 0);

    // BFS
    map<vi, int> dist;
    map<vi, vi> parent;
    map<vi, vi> used_divisor;
    queue<vi> q;

    dist[exp_n] = 0;
    q.push(exp_n);

    while (!q.empty()) {
        vi curr = q.front(); q.pop();
        if (curr == exp_m) break;

        for (const vi& add : divisor_exponents) {
            vi next = curr;
            for (int i = 0; i < k; ++i)
                next[i] = min(next[i] + add[i], exp_m[i]);

            if (!dist.count(next)) {
                dist[next] = dist[curr] + 1;
                parent[next] = curr;
                used_divisor[next] = add;
                q.push(next);
            }
        }
    }

    if (!dist.count(exp_m)) return -1;

    // Recover path
    vector<vi> path_divisors;
    vi curr = exp_m;
    while (curr != exp_n) {
        path_divisors.push_back(used_divisor[curr]);
        curr = parent[curr];
    }
    reverse(path_divisors.begin(), path_divisors.end());

    // output
    printf("%d ", (int)path_divisors.size());
    for (const vi& exp : path_divisors) {
        int d = 1;
        for (int i = 0; i < k; ++i) d *= pow(base[i], exp[i]);
        printf("%d ", d);
    }

    return -2;
}

inline void solve() {
    int res = process();
    if (res != -2) printf("%d\n", res);
    else printf("\n");
}

signed main() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}