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

const int MaxDigit = 9;

struct Node {
    int end;
    Node* child[MaxDigit + 1];

    Node() {
        end = 0;
        fill(child, child + MaxDigit + 1, nullptr);
    }
};

const int MaxN = 10001;
const int MaxNode = 400000;

int cnt = 0;
bool valid = true;
Node nodes[MaxNode + 1];
Node* root;

Node* createNode() {
    new (&nodes[cnt]) Node();
    return &nodes[cnt++];
}

void addNode(string& digits) {
    Node* cur = root;
    for(char& c : digits) {
        int d = c - '0';
        if (!cur->child[d]) cur->child[d] = createNode();
        cur = cur->child[d]; 
    }
    cur->end++;
}

void DFS(Node* u, bool prev) {
    if (!valid) return;
    FOR(d, 0, MaxDigit) {
        Node* v = u->child[d];
        if (v) {
            if (prev && v->end > 0) {
                valid = false;
                return;
            }
            DFS(v, (prev || v->end > 0));
        }
    }
}

void solve() {
    // reset
    cnt = 0;
    valid = true;
    root = createNode();

    // input
    int N; cin >> N;
    FOR(i, 1, N) {
        string digits; cin >> digits;
        addNode(digits);
    }

    // process
    DFS(root, 0);
    cout << (valid ? "YES\n" : "NO\n");
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