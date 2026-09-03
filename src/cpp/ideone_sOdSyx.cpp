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

string s;

struct Node {
    int val, pref, suff;
    static Node base () { return { 0, 0, 0 }; }
    static Node merge(Node& L, Node& R) {
        Node ans = Node::base();
        int k = min(L.suff, R.pref);
        ans.val = L.val + R.val + 2 * k;
        ans.pref = R.pref - k + L.pref;
        ans.suff = L.suff - k + R.suff;
        return ans;
    }
};

struct SegTree{
    int n;
    vector<Node> node;

    SegTree(int n_) : n(n_) {
        node.assign(4 * n + 1, Node::base());
    }

    void build(int i, int l, int r) {
        if (l == r) {
            if (s[l] == '(') node[i].suff = 1;
            else if (s[l] == ')') node[i].pref = 1;
            return;
        }

        int m = (l + r) >> 1;
        build(i << 1, l, m);
        build(i << 1 | 1, m + 1, r);
        node[i] = Node::merge(node[i << 1], node[i << 1 | 1]);
    }

    Node query(int i, int l, int r, int u, int v) {
        if (r < u || l > v || l > r || u > v) return Node::base();
        if (u <= l && r <= v) return node[i];

        int m = (l + r) >> 1;
        Node L = query(i << 1, l, m, u, v);
        Node R = query(i << 1 | 1, m + 1, r, u, v);
        return Node::merge(L, R);
    }
};

inline void solve() {
    cin >> s;
    int n = (int)s.size();
    SegTree tree(n);
    s = '0' + s;
    tree.build(1, 1, n);

    int q; cin >> q;
    while(q--) {
        int l, r; cin >> l >> r;
        printf("%d\n", tree.query(1, 1, n, l, r).val);
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