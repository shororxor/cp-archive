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
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define FORD(i,l,r) for(int i=(l);i>=(r);i--)
#define REPD(i,l,r) for(int i=(l);i>(r);i--)
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

/** This is the end of my template **/

struct Line {
    double a, b;

    Line(double a = 0, double b = 0) : a(a), b(b) {}

    inline double intersect(const Line& other) const {
        return (other.b - b) / (a - other.a);
    }

    inline double eval(double x) {
        return a * x + b;
    }

    bool operator<(const Line& other) const {
        if (this->a == other.a) return this->b > other.b;
        return this->a < other.a;
    }
};

struct CHT {
    deque<Line> dq;

    inline bool valid(const Line& l1, const Line& l2, const Line& l3) {
        return l3.intersect(l2) > l2.intersect(l1);
    }

    inline void build(const Line& newline) {
        while(sz(dq) >= 2 && !valid(dq[sz(dq) - 2], dq[sz(dq) - 1], newline)) {
            dq.pop_back();
        }
        dq.push_back(newline);
    }

    inline double query(double x) {
        int L = 0, R = sz(dq) - 1;
        double ans = dq[R].eval(x);
        while(L < R) {
            int M = (L + R) >> 1;
            if (dq[M].intersect(dq[M + 1]) >= x) {
                ans = dq[M].eval(x);
                R = M;
            }
            else L = M + 1;
        }
        return ans;
    }
};

const int MaxN = 100;
Line lines[MaxN + 1];

inline void solve() {
    int n, q; cin >> n >> q;
    FOR(i, 1, n) cin >> lines[i].a >> lines[i].b;
    sort(lines + 1, lines + n + 1);

    CHT cht;
    FOR(i, 1, n) cht.build(lines[i]);

    while(q--) {
        double x; cin >> x;
        printf("Max y eval at %.2f is %.2f\n", x, cht.query(x));
    }
}

/** This is the end of my solution **/

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