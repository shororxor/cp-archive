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
#define all(v) v.begin(), v.end()
#define all1(v) v.begin()+1, v.end()
#define sz(v) (int)v.size();
#define sqr(x) ((x) * (x))
#define pii pair<int, int>
#define piii pair<int, pii>
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

int n, k;
vector<int>pre;
vector<int>a;

const int MaxN = 1e5+1;

bool check(int x)
{
    int left = 1;
    int next = x + pre[left-1];
    
    auto up = upper_bound(all1(pre), next);
    int right = up - pre.begin() - 1;

    int num_segment = 1;

    while(num_segment < k) {
        
        if (right >= n-(k-1)+(left-1)) {
            return true;
        }
        else {
            left = right + 1;
            next = x + pre[left-1];
            
            up = upper_bound(all1(pre), next);
            right = up - pre.begin() - 1;

            num_segment++;
        }
    }
    
    return right == n;
}


void solve()
{
    cin >> n >> k;
    a.assign(n + 1, 0);
    pre.assign(n+1, 0);

    int L=0;
    FOR(i,1,n) {
        cin >> a[i];
        pre[i] = pre[i-1] + a[i];
        maximize(L, a[i]);
    }

    int R=1e9 * MaxN;
    int ans=0;

    while(L <= R) {
        int M = (L + R) >> 1;
        if(check(M)) {
            ans = M;
            R = M - 1;
        }
        else L = M + 1;
    }

    cout << ans;
}
    
#undef int
int main() {
    init();
    solve();
}