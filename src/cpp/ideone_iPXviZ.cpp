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
#define BITSET(size, x) std::bitset<size + 1>(x).to_string().c_str()
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int,int>
#define complex complex<long double>

const int POSINF = 1e9;
const int NEGINF = -1e9;
const int MOD = 1000000007;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

int cnt[26];

struct SegTree {
    int n;
    vector<int> sum[26];
    vector<int> lazy[26];

    SegTree(int n_) : n(n_) {
        FOR(i, 0, 25) {
            sum[i].assign(4 * n + 1, 0);
            lazy[i].assign(4 * n + 1, -1);
        }
    }

    void pushDown(int i, int l, int r, int m, int ch) {
        if (lazy[ch][i] == -1) return;
        sum[ch][i << 1] = lazy[ch][i] * (m - l + 1);
        sum[ch][i << 1 | 1] = lazy[ch][i] * (r - (m + 1) + 1);
        lazy[ch][i << 1] = lazy[ch][i];
        lazy[ch][i << 1 | 1] = lazy[ch][i];
        lazy[ch][i] = -1;
    }

    void update(int i, int l, int r, int u, int v, int ch, int val) {
        if (r < u || l > v || l > r || u > v) return;
        if (u <= l && r <= v) {
            sum[ch][i] = val * (r - l + 1);
            lazy[ch][i] = val; 
            return;
        }

        int m = (l + r) >> 1;
        this->pushDown(i, l, r, m, ch);
        update(i << 1, l, m, u, v, ch, val);
        update(i << 1 | 1, m + 1, r, u, v, ch, val);
        sum[ch][i] = sum[ch][i << 1] + sum[ch][i << 1 | 1];
    }

    int query(int i, int l, int r, int u, int v, int ch) {
        if (r < u || l > v || l > r || u > v) return 0;
        if (u <= l && r <= v) return sum[ch][i];

        int m = (l + r) >> 1;
        this->pushDown(i, l, r, m, ch);
        int L = query(i << 1, l, m, u, v, ch);
        int R = query(i << 1 | 1, m + 1, r, u, v, ch);
        return L + R;
    }

    void update(int u, int v, int ch, int val) {
        this->update(1, 1, n, u, v, ch, val);
    }

    int query(int u, int v, int ch) {
        return this->query(1, 1, n, u, v, ch);
    }
};

inline void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    s = '0' + s;

    SegTree tree(n);
    FOR(i, 1, n) tree.update(i, i, s[i] - 'a', 1);

    while(q--) {
        int l, r, k; cin >> l >> r >> k;
        
        // counting sort
        FOR(ch, 0, 25) {
            cnt[ch] = tree.query(l, r, ch);
            tree.update(l, r, ch, 0);
        }

        if (k == 1) {
            int L = l;
            FOR(ch, 0, 25) {
                if (cnt[ch] > 0) {
                    tree.update(L, L + cnt[ch] - 1, ch, 1);
                    L += cnt[ch];
                }
            }
        }
        else {
            int L = l;
            FORD(ch, 25, 0) {
                if (cnt[ch] > 0) {
                    tree.update(L, L + cnt[ch] - 1, ch, 1);
                    L += cnt[ch];
                }
            }
        }
    }

    // output
    FOR(i, 1, n) {
        FOR(ch, 0, 25) {
            if (tree.query(i, i, ch)) {
                cout << (char)(ch + 'a');
                break;
            }
        }
    }
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