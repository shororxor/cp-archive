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
    int L,R,I;
    Segment() : L(0), R(0), I(0) {}
    Segment(int L, int R, int I) : L(L), R(R), I(I) {};
    bool operator<(const Segment& other) const {
        return R < other.R;
    }
};

struct Customer
{
    int arrival, departure, index;
    Customer(int arrival, int departure, int index) 
        : arrival(arrival), departure(departure), index(index) {};
    Customer() : arrival(0), departure(0), index(0) {};

    bool operator<(const Customer& other) {
        return arrival < other.arrival;
    }
};

vector<Customer> customers;

void solve()
{
    int n; cin >> n;
    customers.assign(n + 1, {0,0,0});
    FOR(i,1,n) {
        cin >> customers[i].arrival >> customers[i].departure;
        customers[i].index = i;
    }
    sort(all1(customers));

    priority_queue<pii, vector<pii>, greater<pii>> minheap;
    vector<int> rooms(n+1, 0);
    int num=1;

    FOR(i,1,n) {
        if (!minheap.empty() && minheap.top().first < customers[i].arrival) {
            rooms[customers[i].index] = minheap.top().second;
            minheap.pop();
            minheap.push({customers[i].departure, rooms[customers[i].index]});
        }
        else {
            rooms[customers[i].index] = num++;
            minheap.push({customers[i].departure, rooms[customers[i].index]});
        }
    }

    cout << num - 1 << '\n';
    FOR(i,1,n) cout << rooms[i] << ' ';
}

#undef int
int main() {
    init();
    solve();
}