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
#define mask(i) (1LL << (i)) // 2^i
#define bit(x, i)  (((x) >> (i)) & 1)
#define onbit(x, i) ((x) = (x) | mask(i))
#define offbit(x, i) ((x) = (x) & (~mask(i)))
#define pcount(i) __builtin_popcount(i)
#define bctz(i) __builtin_ctz(i)
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sz(v) (int)v.size();
#define sqr(x) ((x) * (x))
#define FOR(i,l,r) for(auto i=(l);i<=(r);i++)
#define REP(i,l,r) for(auto i=(l);i<(r);i++)
#define FORD(i,l,r) for(auto i=(l);i>=(r);i--)
#define REPD(i,l,r) for(auto i=(l);i>(r);i--)
#define pii pair<int,int>

const int inf = 1e9+1;
const int MOD = 1e9+7;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

struct Segment
{
    int x,y;
    Segment() : x(0), y(0) {}
    Segment(int x, int y) : x(x), y(y) {}
    bool operator<(const Segment& other) const {
        return y < other.y;
    }
};

const int MaxN = 2e5+5;

int n;
bool used[MaxN];
Segment a[MaxN];
pii b[MaxN];

bool search(Segment& cur, int& cur_index) {
    int L = 1;
    int R = n;
    int X = -1;
    while(L <= R) {
        int M = (L + R) >> 1;
        if (!used[b[M].second] && b[M].first >= cur.y) {
            R =  M - 1;
            X = b[M].second;
        }
        else L = M + 1;
    }
    if(X == -1) return false;
    else {
        int ans_index = -1;
        int min_right = inf;
        
        FORD(i, X-1, cur_index+1) {
            if (a[i].x > cur.y && a[i].y < a[X].y) {
                X = i;
            }
        }
        
        cur_index = X;
        return true;
    }
}

void solve()
{
    cin >> n;

    FOR(i,1,n) cin >> a[i].x >> a[i].y;
    sort(a+1, a+n+1);

    FOR(i,1,n) b[i] = {a[i].x, i};
    sort(b+1, b+n+1);

    int ans = 1;
    int cur_index = 1;
    while(true) {
        Segment cur = a[cur_index];
        used[cur_index] = true;
        if (!search(cur, cur_index)) break;
        ans++;
    }
    cout << ans;
}

#undef int
int main() {
    init();
    solve();
}