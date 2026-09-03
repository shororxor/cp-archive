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
// #define int ll
#define mask(i) (1LL << (i))
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcountll(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sqr(x) ((x) * (x))
#define pii pair<int, int>
#define piii pair<pii, int>
#define FOR(i,l,r) for(auto i=(l);i<=(r);i++)
#define REP(i,l,r) for(auto i=(l);i<(r);i++)
#define FORD(i,l,r) for(auto i=(l);i>=(r);i--)
#define REPD(i,l,r) for(auto i=(l);i>(r);i--)
#define complex complex<long double>

const int neginf = INT_MIN;
const int posinf = INT_MAX;
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
const int MaxNodes = 2e6;
const int MaxAlphabet = 26;

const int MOD[] = {(int)1e9 + 2277, (int)1e9 + 5277, (int)1e9 + 8277, (int)1e9 + 9277};
const int NMOD = 1;
const int BASE = 256;

int numWords;
string words[MaxN + 1];

int len[MaxN + 1]; // 8MB
int POW[NMOD][MaxN + 1]; // 8MB
int HS[NMOD][MaxN << 1 | 1], RHS[NMOD][MaxN << 1 | 1]; // 32MB
int sta[MaxN + 1], fin[MaxN + 1]; // 16MB

struct Node {
    Node* child[MaxAlphabet]; // 208 bytes
    int real, fake; // 16 bytes

    Node() {
        fill(child, child + MaxAlphabet, nullptr);
        real = 0;
        fake = 0;
    }
};

int cnt = 0;
ll ans = 0;
Node nodes[MaxNodes + 1]; // 448 MB
Node* root;

Node* createNode(void) {
    return &nodes[cnt++];
}

void addString(string& s, bool isRev) {
    Node* cur = root;
    for(auto& ch : s) {
        int c = ch - 'a';
        if (cur->child[c] == nullptr) {
            cur->child[c] = createNode();
        }
        cur = cur->child[c];
    }
    if (isRev) cur->fake++; else cur->real++;
}

void calHash(string& s, int (&hs)[NMOD][MaxN << 1 | 1], int start, int len) {
    FOR(j, 0, NMOD - 1) {
        hs[j][start] = 0;
        FOR(i, 1, len) hs[j][start + i] = (1LL * hs[j][start + i - 1] * BASE + s[i - 1]) % MOD[j];
    }
}

int getHash(int (&hs)[NMOD][MaxN << 1 | 1], int j, int start, int l, int r) {
    int res = (hs[j][start + r] - 1LL * hs[j][start + l - 1] * POW[j][r - l + 1]) % MOD[j];
    return res < 0 ? res + MOD[j] : res;
}

bool isPalin(int i, int u, int v) {
    FOR(j, 0, NMOD - 1) {
        if (getHash(HS, j, sta[i], u, v) != getHash(RHS, j, sta[i], len[i] - v + 1, len[i] - u + 1)) {
            return false;
        }
    }
    return true;
}

void traverse(int id, bool isRev) {
    Node* cur = root;
    const string &s = words[id];

    if (!isRev) {
        FOR(j, 1, len[id] - 1) {
            cur = cur->child[s[j - 1] - 'a'];
            if (isPalin(id, j + 1, len[id])) ans += cur->fake;
        }
    }

    else {
        FORD(j, len[id], 2) {
            cur = cur->child[s[j - 1] - 'a'];
            if (isPalin(id, 1, j - 1)) ans += cur->real;
        }
    }

    if (!isRev) {
        cur = cur->child[s.back() - 'a'];
        ans += cur->fake;
    }
}

void solve() {
    // input
    cin >> numWords;
    FOR(i, 1, numWords) {
        cin >> len[i] >> words[i];
    }

    // compute pow
    FOR(j, 0, NMOD - 1) {
        POW[j][0] = 1;
        FOR(i, 1, MaxN) POW[j][i] = (1LL * POW[j][i - 1] * BASE) % MOD[j];
    }

    // build combined hash and trie
    root = createNode();
    sta[0] = fin[0] = -1;

    FOR(i, 1, numWords) {
        sta[i] = fin[i - 1] + 1;
        fin[i] = sta[i] + len[i];

        calHash(words[i], HS, sta[i], len[i]);
        addString(words[i], false);

        string revWord = words[i];
        reverse(all(revWord));

        calHash(revWord, RHS, sta[i], len[i]);
        addString(revWord, true);
    }

    FOR(i, 1, numWords) {
        traverse(i, false);
        traverse(i, true);
    }

    printf("%lld\n", ans);
}

/** This is the end of my solution **/

// #undef int
int main(void) {
    init();
    solve();
    return 0;
}
