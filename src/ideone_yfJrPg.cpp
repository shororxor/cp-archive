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

const int MaxN = 1e6;
const int MaxLog = 20;
const int MaxAlphabet = 26;

int LOG2[MaxN + 1];
int val[MaxN + 1]; // save the value of the node (not index)
int tree[MaxN + 1][MaxLog + 1]; // just save the index of parent

struct Node {
    char name;
    int depth; // the length of string
    Node* childs[MaxAlphabet];
    Node* par[MaxLog + 1];

    Node() {
        fill(childs, childs + MaxAlphabet, nullptr);
        fill(par, par + MaxLog + 1, nullptr);
        depth = 0;
    }
};

int cnt = 0;
Node* root; // zero root
Node nodes[MaxN + 1]; // allocation
Node* id[MaxN + 1]; // input is id of node on trie -> return pointer of that node 

Node* createNode() {
    id[cnt] = &nodes[cnt];
    return id[cnt++];
}

void prepare() {
    LOG2[1] = 0;
    FOR(i, 2, MaxN) LOG2[i] = LOG2[i / 2] + 1;
}

void solve() {
    int N; cin >> N;
    char operation;
    root = createNode();
    Node* cur = root;

    int i = 1;
    FOR(k, 1, N) {
        cin >> operation;
        if (operation == 'T') {
            char value; cin >> value;

            // create node on trie
            Node* child = cur->childs[value - 'a'];
            if (child == nullptr) child = createNode();
            child->name = value;

            // update parent on trie
            child->par[0] = cur;
            FOR(j, 1, LOG2[N]) if (child->par[j - 1]) child->par[j] = child->par[j-1]->par[j-1];
            child->depth = cur->depth + 1;
            cur = child;

            // update par for tree
            val[i] = cnt - 1;
            tree[i][0] = i - 1;
            FOR(j, 1, LOG2[N]) tree[i][j] = tree[tree[i][j - 1]][j - 1];
            i++;
        }

        else if (operation == 'U') {
            // move back on tree
            int value; cin >> value;
            int n = i - 1;
            FORD(j, LOG2[N], 0) if (value & (1 << j)) n = tree[n][j];

            // update pointer cur
            val[i] = val[n];
            cur = id[val[i]];

            // update par for tree
            tree[i][0] = i - 1;
            FOR(j, 1, LOG2[N]) tree[i][j] = tree[tree[i][j - 1]][j - 1];
            i++;
        }

        else if (operation == 'P') {
            int value; cin >> value;
            Node* p = cur;
            value = p->depth - 1 - value;
            FORD(j, LOG2[N], 0) if (value & (1 << j)) p = p->par[j];
            cout << p->name << '\n';
        }
    }
}

/** This is the end of my solution **/
 
#undef int
int main(void) {
    init();
    prepare();
    solve();
    return 0;
}