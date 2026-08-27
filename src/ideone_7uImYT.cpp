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

int n, k; 

int f(int x) {
    return x - x/k;
}

void solve() {
    cin >> k >> n;

    int L = 0;
    int R = 1e18;

    int ans = -1;
    while(L <= R) {
        int M = (L + R) >> 1;
        if (f(M) >= n) {
            ans = M;
            R = M - 1;
        }
        else L = M + 1;
    }

    cout << ans << '\n';
}

#undef int
int main() {
    init();
    int T; cin >> T;
    while(T--) solve();
}

/*
Gọi f(x) là một hàm return số lượng số không chia hết cho k
=> số thứ N không chia hết cho k => tìm x sao cho f(x) = N
và khi mà có một số không chia hết cho k => chỗ f(x) đó sẽ tăng lên => tìm x min

trong một range [k, X] => số lượng số chia hết cho k là X / k 
mà tổng lượng số là X => số lượng số không chia hết cho k là X - X/k;

1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18

X = 18
x / 3 = 6 {3, 6, 9, 12, 15, 18}

18 - 6 = 12

17 / 3 = 5 
17 - 5 = 12

16 / 3 = 5
16 / 3 = 11

*/