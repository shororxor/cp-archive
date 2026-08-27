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
#define REP(i, r) for(int i=0;i<(r);i++)
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>
#define ite std::vector<int>::iterator

template <class T> bool minimize(T& x,T y) {
    if (x > y) x = y; else return 0; return 1;
}
 
template <class T> bool maximize(T& x,T y) {
    if (x < y) x = y; else return 0; return 1;
}

// data structures
struct Factor {
    int m, x, mx;
    Factor(int m_=0, int x_=0, int mx_=0) : m(m_), x(x_), mx(mx_) {}
    static Factor makeDefault() { return Factor(); }
};

struct Congruence {
    int a, m;
    Congruence(int a_=0, int m_=1) : a(a_), m(m_) {}
    void process() { a = (a % m + m) % m; }
};

const int mod = 142857;

int nmods;
vector<Factor> mods;

// preparation
void factorization() {
    int m = mod;
    mods.push_back(Factor::makeDefault());
    for(int i = 2; i*i <= m; i++) {
        if (m % i == 0) {
            int cnt = 0;
            int prod = 1;
            while(m % i == 0) {
                m /= i;
                prod *= i;
                cnt++;
            }
            mods.push_back(Factor(i, cnt, prod));
        }
    }
    if (m > 1) mods.push_back(Factor(m, 1, m));
    nmods = (int)mods.size() - 1;
}

// utility functions
int extended_euclid(int a, int b, int& x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int g = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int inverse_mod(int a, int m) {
    int x, y;
    int g = extended_euclid(a, m, x, y);
    assert(g == 1);
    x = (x % m + m) % m;
    return x;
}

int fastpow(int a, int b, int m) {
    a %= m;
    int res = 1;
    while(b) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

// specific utility functions
int v_fact(int n, int p) {
    int res = 0;
    while(n > 0) { n /= p; res += n; }
    return res;
}

int prod_cycle(Factor factor) {
    int res = 1;
    FOR(i, 1, factor.mx) if (i % factor.m) res = (res * i) % factor.mx;
    return res;
}

// F(n) = B(n) * F(n / m)
int factor_without_m_mod(int n, int cycle, Factor factor) {
    if (n == 0) return 1;
    int res = 1;
        
    // B(n) = cyclic product * remainder part
    res = res * fastpow(cycle, n / factor.mx, factor.mx) % factor.mx;
    FOR(i, 1, n % factor.mx) if (i % factor.m) res = (res * i) % factor.mx;

    // recursion for n / m
    res = (res * factor_without_m_mod(n / factor.m, cycle, factor)) % factor.mx;
    return res;
}

// main nCk for each prime with power
int nCk_mod_prime_pow(int n, int k, Factor factor) {
    int alpha = v_fact(n, factor.m) - v_fact(k, factor.m) - v_fact(n - k, factor.m);
    if (alpha >= factor.x) return 0; // nCk divisible by m^x

    int cycle = prod_cycle(factor);
    int nom = factor_without_m_mod(n, cycle, factor);
    int den1 = factor_without_m_mod(k, cycle, factor);
    int den2 = factor_without_m_mod(n - k, cycle, factor);
    int den = inverse_mod((den1 * den2) % factor.mx, factor.mx);

    int res = fastpow(factor.m, alpha, factor.mx);
    res = (res * nom) % factor.mx;
    res = (res * den) % factor.mx;
    return res;
}

// Chinese remainder theorem
Congruence CRT(vector<Congruence> eqs) {
    Congruence res;
    FOR(i, 1, nmods) res.m = res.m * eqs[i].m;
    FOR(i, 1, nmods) {
        int prod = 1;
        prod = (prod * eqs[i].a) % mod;
        prod = (prod * (res.m / eqs[i].m)) % mod;
        prod = (prod * inverse_mod(res.m / eqs[i].m, eqs[i].m)) % mod;
        res.a += prod % mod;
    }
    res.process();
    return res;
}

// main nCk
void nCk_mod_M() {
    int n, k; cin >> n >> k;
    vector<Congruence> eqs(nmods + 1);
    FOR(i, 1, nmods) eqs[i].a = nCk_mod_prime_pow(n, k, mods[i]), eqs[i].m = mods[i].mx;
    cout << CRT(eqs).a << '\n';
}

signed main() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    factorization();
    int T; cin >> T; while(T--) nCk_mod_M();
    return 0;
}
