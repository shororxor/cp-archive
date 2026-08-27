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
const int inf = 1e9+1;
const int MOD = 1e9+7;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

int n, m;
vector<int>height,min_left,min_right;

int compute_rectangle()
{
    stack<int> st1, st2;

    min_left.assign(m+1,0);
    min_right.assign(m+1,m+1);

    // find min left
    FOR(i,1,m) {
        while(st1.size() && height[st1.top()] > height[i]) {
            min_right[st1.top()] = i;
            st1.pop();
        }
        st1.push(i);
    }

    // find min right
    FORD(i,m,1) {
        while(st2.size() && height[st2.top()] > height[i]) {
            min_left[st2.top()] = i;
            st2.pop();
        }
        st2.push(i);
    }

    int area=0;
    int w,h;
    FOR(i,1,m) {
        w = (min_right[i] - 1) - (min_left[i] + 1) + 1;
        h = height[i];
        maximize(area, h*w);
    }
    return area;
}

void solve()
{
    cin >> n >> m;
    height.assign(m+1,0);

    int ans = 0;
    FOR(i,1,n) {
        int x;
        FOR(j,1,m) {
            cin >> x;
            if (x) height[j] += 1;
            else height[j] = 0;
        }
        ans = max(ans, compute_rectangle());
    }
    cout << ans;
}

#undef int
int main() {
    init();
    solve();
}