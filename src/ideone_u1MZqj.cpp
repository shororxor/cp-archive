#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define int ll
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

const int INF = 2;
const double EPS = 1e-9;

inline void print(const vector<vector<double>>& a) {
    cout << "\n";
    int n = (int)a.size() - 1;
    int m = (int)a[0].size() - 1;
    FOR(i, 1, n) {
        FOR(j, 1, m) {
            cout << fixed << setprecision(2) << setw(8) << a[i][j] << " ";
        }
        cout << '\n';
    }
}

inline int gauss(vector<vector<double>>& a, vector<double>& ans) {
    int n = (int)a.size() - 1;
    int m = (int)a[0].size() - 2;

    vector<int> where(m + 1, -1);

    for(int col = 1, row = 1; col <= m && row <= n; col++) {
        int pivot = row;
        FOR(i, row, n) if (abs(a[i][col]) > abs(a[pivot][col])) pivot = i;

        if (abs(a[pivot][col]) < EPS) continue;
        FOR(j, col, m + 1) swap(a[pivot][j], a[row][j]);
        where[col] = row;

        FOR(i, 1, n) {
            if (i != row) {
                double c = a[i][col] / a[row][col];
                FOR(j, col, m + 1) a[i][j] -= a[row][j] * c;
            }
        }
        ++row;
    }

    print(a);

    ans.assign(m + 1, 0);
    FOR(j, 1, m) if (where[j] != -1) ans[j] = a[where[j]][m + 1] / a[where[j]][j];
    FOR(i, 1, n) {
        double sum = 0;
        FOR(j, 1, m) sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m + 1]) > EPS) return 0;
    }

    FOR(j, 1, m) if (where[j] == -1) return INF;
    return 1;
}

inline void solve() {
    int n, m; cin >> n >> m;
    vector<vector<double>> a(n + 1, vector<double>(m + 2));
    FOR(i, 1, n) FOR(j, 1, m + 1) cin >> a[i][j];
    print(a);

    vector<double> sol;
    int result = gauss(a, sol);

    if (result == 0) cout << "no solution\n";
    else if (result == INF) cout << "infinite solution\n";
    else cout << "unique solution:\n";
    FOR(i, 1, m) cout << "x" << i << " = " << sol[i] << "\n";
}

signed main() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}