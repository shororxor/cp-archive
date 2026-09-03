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

struct Data
{
    int cnt=0;
    deque<int> dq;
};

void solve()
{
    int n, x;
    cin >> n >> x;
    vector<int>a(n+1,0);
    FOR(i,1,n) cin >> a[i];

    sort(all1(a));
    int ak = x - a[1];

    auto lb = upper_bound(all1(a), ak);

    // edge case
    if (lb - a.begin() == 1) {
        cout << n << '\n';
        return;
    }

    int b = lb - a.begin() - 1;
    int aj = a[b];
    int ans = n - b + 1;

    int i=2;
    int j=b-1;
    while(i <= j) {
        int L = a[i] - a[1];
        int R = a[b] - a[j];
        if (L - R <= ak - aj) {
            ans++;
            i++;
            j--;
        }
        else {
            j--; ans++;
        }
    }
    cout << ans;
}

#undef int
int main() {
	init();
	solve();
}