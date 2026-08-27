#include <bits/stdc++.h>
#include <csignal>
#include <unistd.h>
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
#define FOR(i,l,r) for(auto i=(l);i<=(r);i++)
#define REP(i,l,r) for(auto i=(l);i<(r);i++)
#define FORD(i,l,r) for(auto i=(l);i>=(r);i--)
#define REPD(i,l,r) for(auto i=(l);i>(r);i--)

template <class T> bool minimize(T &x,T y){
    if (x>y) x=y; else return 0; return 1;
}

template <class T> bool maximize(T &x,T y){
    if (x<y) x=y; else return 0; return 1;
}

const int inf = 1e9;
const int MOD = 1e9+7;
const double PI = 3.14159265359;

const int maxN = 1e5 + 1;
int a[maxN];

void solve() 
{
	int n, q, x;
	cin >> n >> q;

	FOR(i,1,n) cin >> a[i];
	FOR(i,1,q) {
		cin >> x;
		int l=1, r=n;
		while(l <= r) {
			int m = (l + r) / 2;
			if (a[m] == x) {
				cout << m << '\n';
				break;
			}
			else if (a[m] > x) {
				r = m - 1;
			}
			else l = m + 1;
		}
	}
}

#undef int
int main()
{
	init();
	solve();
}