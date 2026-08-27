#include <bits/stdc++.h>
using namespace std;
using namespace std::complex_literals;

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

struct Node {
    int depth, value;
    Node* child[2];

    Node() {
        value = -1;
        depth = 0;
        fill(child, child + 2, nullptr);
    }
};

int cnt;
const int MaxNodes = 1e3;
Node nodes[MaxNodes + 1];
Node* root;

set<int> depth[32];

Node* createNode() {
    new (&nodes[cnt]) Node();
    return &nodes[cnt++];
}

void addNum(int x) {
    Node* cur = root;
    FORD(i, 30, 0) {
        int b = bit(x, i);
        if (!cur->child[b]) {
            cur->child[b] = createNode();
            cur->child[b]->value = b;
        }
        cur = cur->child[b];
    }
}

void DFS(Node* u) {
    FOR(i, 0, 1) {
        Node* v = u->child[i];
        if (v) {
            v->depth = u->depth + 1;
            depth[v->depth].insert(i);
            DFS(v);
        }
    }
}

void solve() {
    cnt = 0;
    root = createNode();
    FOR(i, 0, 31) depth[i].clear();

    int N; cin >> N;
    FOR(i, 1, N) {
        int x; cin >> x;
        addNum(x);
    }

    DFS(root);

    int ans = 0;
    FOR(i, 1, 31) {
        if ((int)depth[i].size() == 2) {
            ans |= (1 << (31 - i));
        }   
    }

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

    int T; cin >> T;
    while(T--) solve();
}