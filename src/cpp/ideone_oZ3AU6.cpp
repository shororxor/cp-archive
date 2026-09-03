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
    int id, end, depth;
    char value;
    Node* child[4];

    Node() {
        id = 0; end = 0; depth = 0;
        value = 'n';
        fill(child, child + 4, nullptr);
    }
};

const int MaxNodes = 2500000;
char letters[4] = {'A', 'C', 'G', 'T'};

int cnt, ans;
int subtree[MaxNodes + 1];
Node nodes[MaxNodes + 1];
Node* root;

Node* createNode() {
    new (&nodes[cnt]) Node();
    return &nodes[cnt++];
}

int getGen(char& inp) {
    switch(inp) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
    }
    return 0; // default
}

void addGen(string& gen) {
    Node* cur = root;
    for(auto& ch : gen) {
        int g = getGen(ch);
        if (!cur->child[g]) {
            cur->child[g] = createNode();
            cur->child[g]->id = cnt - 1;
            cur->child[g]->value = ch;
        }
        cur = cur->child[g];
    }
    cur->end++;
}

void countSubtree(Node* u) {
    subtree[u->id] = u->end;
    for(auto& ch : letters) {
        int g = getGen(ch);
        Node* v = u->child[g];
        if (v) {
            v->depth = u->depth + 1;
            countSubtree(v);
            subtree[u->id] += subtree[v->id];
        }
    }
    maximize(ans, subtree[u->id] * u->depth);
}

void solve() {
    cnt = 0; ans = 0;
    root = createNode();
    root->id = cnt - 1;

    int N; cin >> N;
    FOR(i, 1, N) {
        string gen; cin >> gen;
        addGen(gen);
    }

    countSubtree(root);
    printf("%lld\n", ans);
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
    FOR(t, 1, T) {
        printf("Case %d: ", t);
        solve();
    }
}