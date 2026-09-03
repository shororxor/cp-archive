#include <bits/stdc++.h>
using namespace std;
	
void init() 
{
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
const int inf = 1e9;
const int MOD = 1e9+7;
const double PI = 3.14159265359;

template <class T> bool minimize(T &x,T y){
	if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
	if (x<y) x=y; else return 0; return 1;
}

int n;
vector<int> a;

int binary_search_left(int start, int target) {

	int l=start, r=n;
	int ans = -1;

	while(l <= r) {
		int m = (r + l) / 2;
		if (a[m] < target) {
			l = m + 1;
		}
		else if (a[m] >= target) {
			ans = m;
			r = m - 1;
		}
	}

	return ans;
}

int binary_search_right(int start, int target) {

	int l=start, r=n;
	int ans = -1;

	while(l <= r) {
		int m = (r + l) / 2;
		if (a[m] > target) {
			r = m - 1;
		}
		else if (a[m] <= target) {
			ans = m;
			l = m + 1;
		}
	}

	return ans;
}

void solve()
{
	int L, R;
	cin >> n >> L >> R;

	a.assign(n + 1, 0);
	FOR(i,1,n) cin >> a[i];
	sort(all(a));

	int ans = 0;

	FOR(i,1,n) {
		int left_bound = max(1LL * 0,  L - a[i]);
		int right_bound = R - a[i];
		
		int l = binary_search_left(i+1, left_bound);
		int r = binary_search_right(i+1, right_bound);

		if (l != -1 && r != -1 && l <= r) ans += (r - l + 1);
	}

	cout << ans << '\n';
}
	
#undef int
int main()
{
	init();
	solve();
}