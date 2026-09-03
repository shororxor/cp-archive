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

void solve()
{
    string n; int k;
    cin >> n >> k;
    int sz = n.size();
    n = '0' + n;

    stack<char>st;

    FOR(i, 1, sz) {
        while(k > 0 && st.size() && n[i] < st.top()) {
            st.pop();
            k--;
        }
        st.push(n[i]);
    }

    while(k > 0) {
        st.pop();
        k--;
    }

    string ans = "";
    while(st.size()) {
        ans += st.top();
        st.pop();
    }

    while(ans.back() == '0') ans.pop_back();
    reverse(all(ans));
    cout << (ans.size() > 0 ? ans : "0"); 
}

#undef int
int main() {
    init();
    solve();
}