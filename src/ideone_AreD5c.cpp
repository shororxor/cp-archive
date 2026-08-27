#include <bits/stdc++.h>
using namespace std;
 
void init() {
    #ifndef ONLINE_JUDGE
    freopen("input.inp", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif
 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
 
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
#define pii pair<int, int>
#define piii pair<int, pii>
#define vi vector<int>
#define vb vector<bool>
#define vii vector<vector<int>>
#define fi first
#define se second
#define pb push_back
#define pf push_front
#define mp make_pair
#define pq priority_queue
#define binary(x, n) (std::bitset<n>(x).to_string())
#define FOR(i,l,r) for(auto i=(l);i<=(r);i++)
#define REP(i,l,r) for(auto i=(l);i<(r);i++)
#define FORD(i,l,r) for(auto i=(l);i>=(r);i--)
#define REPD(i,l,r) for(auto i=(l);i>(r);i--)
const int inf = 1e9+1;
const int MOD = 1e9+7;
const double PI = 3.14159265359;
 
template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}
 
template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

struct triple {
    int x, y, z;
    triple(int x, int y, int z) : x(x), y(y), z(z) {}
};

int ans = 0;
int n, m, x;
vector<int> a;
vector<int> uoc;
vector<triple> cons;

bool check() {
    for(auto &[x, y, z] : cons) {
        if (gcd(a[x], a[y]) != z) {
            return false;
        }
    }
    return true;
}

void backtrack(int i) {

    if (i == n) {
        if (check()) ans++;
        return;
    }

    for(int k=1; k <= x; k++) {
        if (k % uoc[i+1] == 0) {
            a[i+1] = k;
            backtrack(i+1);
        }
    }
}

void solve() {
    cin >> n >> m >> x;
    a.assign(n+1, 0);
    uoc.assign(n+1, 1);

    int i, j, g;
    while(m--) {
        cin >> i >> j >> g;
        uoc[i] *= g;
        uoc[j] *= g;
        cons.push_back({i,j,g});
    }

    backtrack(0);
    cout << ans;
}

#undef int
int main() {
    init();
    solve();
}