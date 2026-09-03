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

void solve()
{
    int n; cin >> n;
    vector<int>a(n+1, 0);
    int m = 0;
    FOR(i,1,n) {
        cin >> a[i];
        m = max(m, a[i]);
    }

    vector<int> ans(n + 1, inf);
    stack<int> st1, st2;

    FOR(i,1,n) {
        while(st1.size() && a[st1.top()] < a[i]) {
            ans[st1.top()] = i;
            st1.pop();
        }
        st1.push(i);
    }

    FORD(i,n,1) {
        while(st2.size() && a[st2.top()] < a[i]) {
            if (ans[st2.top()] != m) {
                int d1 = abs( ans[st2.top()] - st2.top() );
                int d2 = abs( i - st2.top() );
                if (d2 <= d1) ans[st2.top()] = i;
            }
            st2.pop();
        }
        st2.push(i);
    }

    
    FOR(i,1,n) {
        if(a[i] != m) cout << ans[i] << ' ';
        else cout << -1 << ' ';
    }
}

#undef int
int main() {
    init();
    solve();
}