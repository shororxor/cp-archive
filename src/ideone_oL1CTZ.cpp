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

void solve() {
    string s; int k;
    cin >> s >> k;

    int n = s.size();
    s = '0' + s;
    map<char,int> fre;

    int i = 1;
    int j = 1;
    int ans = 0;

    while(j <= n) {
        while(j <= n && fre[s[j]] + 1 <= k) {
            fre[s[j]]++;
            j++;
        }       

        int len = j-i;
        ans += (len * (len + 1)) >> 1;

        if (j <= n) {
            while(fre[s[j]] + 1 > k) {
                fre[s[i]]--;
                i++;
            }
            int len = j - i;
            ans -= (len * (len + 1)) >> 1;
        }
    }   

    cout << ans << '\n';
}

#undef int
int main() {
    init();
    int T; cin >> T;
    while(T--) solve();
}