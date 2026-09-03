#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#define ll long long
#define ull unsigned long long
#define ld long double
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

int fastmul(int x, int y, int m) {
    ull q = (ld)x * y / m;
    int res = ((ull)x * y - q * m);
    if (res >= m) res -= m;
    if (res < 0) res += m;
    return res;
}

int fastpow(int a, int b, int m) {
    if (b == 0) return 1;
    if (b & 1) return fastmul(a, fastpow(a, b - 1, m), m);
    return fastpow(fastmul(a, a, m), b >> 1, m);
}

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

bool millerRabin(int x, int m, int s, int k) {
    x = fastpow(x, s, m);
    if (x == 1) return true;
    while (k--) {
        if (x == m - 1) return true;
        if ((x = fastmul(x, x, m)) == 1) return false;
    }
    return false;
}

bool isPrime(int x) {
    if (x == 2 || x == 3 || x == 5 || x == 7) return true;
    if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
    if (x < 121) return x > 1;
    int s = x - 1;
    int k = 0;
    while (s % 2 == 0) {
        s >>= 1;
        k++;
    }
    if (x < 1LL << 32) {
        for (ll z : {2, 7, 61}) {
            if (!millerRabin(z, x, s, k)) return false;
        }
    } 
    else {
        for (ll z : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            if (!millerRabin(z, x, s, k)) return false;
        }
    }
    return true;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int r) {
    return uniform_int_distribution<int>(0, r - 1)(rng);
}

void pollard(int x, vector<int> &ans) {
    if (isPrime(x)) {
        ans.push_back(x);
        return;
    }
    int c = 1;
    while (true) {
        c = 1 + get_rand(x - 1);
        auto f = [&](int y) {
            int res = fastmul(y, y, x) + c;
            if (res >= x) res -= x;
            return res;
        };
        int y = 2;
        int B = 100;
        int len = 1;
        int g = 1;
        while (g == 1) {
            int z = y;
            for (int i = 0; i < len; i++) {
                z = f(z);
            }
            int zs = -1;
            int lft = len;
            while (g == 1 && lft > 0) {
                zs = z;
                int p = 1;
                for (int i = 0; i < B && i < lft; i++) {
                    p = fastmul(p, abs(z - y), x);
                    z = f(z);
                }
                g = gcd(p, x);
                lft -= B;
            }
            if (g == 1) {
                y = z;
                len <<= 1;
                continue;
            }
            if (g == x) {
                g = 1;
                z = zs;
                while (g == 1) {
                    g = gcd(abs(z - y), x);
                    z = f(z);
                }
            }
            if (g == x) break;
            assert(g != 1);
            pollard(g, ans);
            pollard(x / g, ans);
            return;
        }
    }
}

// return list of all prime factors of x (can have duplicates)
vector<int> factorize(int x) {
    vector<int> ans;
    for (int p : {2, 3, 5, 7, 11, 13, 17, 19}) {
        while (x % p == 0) {
            x /= p;
            ans.push_back(p);
        }
    }
    if (x != 1) pollard(x, ans);
    sort(ans.begin(), ans.end());
    return ans;
}

int phi(int n) {
    vector<int> P = factorize(n);
    ll res = n;
    ll last = -1;
    for (auto& p : P) {
        if (p != last) {
            res = res / p * (p - 1);
            last = p;
        }
    }
    return res;
}

vector<int> generator(int n) {
    int phin = phi(n);
    vector<int> P = factorize(phin);

    vector<int> res;
    for(int g = 2; g <= n - 1; g++) {
        if (gcd(g, n) == 1) {
            bool ok = 1;
            for(int j = 0; j < (int)P.size() && ok; j++) {
                ok &= (fastpow(g, phin / P[j], n) != 1);
            }
            if (ok) res.push_back(g);
        } 
    }
    return res;
}

inline void solve() {
    int n; cin >> n;
    vector<int> g = generator(n);
    for(int& x : g) cout << x << ' ';
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