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

int cnt = 0;
vector<vector<char>> a;
vector<bool> col(9, 0);
vector<bool> L(16, 0);
vector<bool> R(16, 0);

void backtrack(int i) {
    if (i == 8) {
        cnt++;
        return;
    }

    i++;
    FOR(j,1,8) {
        if (a[i][j] != '*' && !col[j] && !L[j-i+8] && !R[i+j-1]) {
            col[j] = 1;
            L[j-i+8] = 1;
            R[i+j-1] = 1;
            
            backtrack(i);
            
            col[j] = 0;
            L[j-i+8] = 0;
            R[i+j-1] = 0;
        }
    }
}

void solve() {
    a.assign(9, vector<char>(9, ' '));
    FOR(i,1,8) FOR(j,1,8) cin >> a[i][j];

    backtrack(0);
    cout << cnt << '\n';
}

#undef int
int main() {
    init();
    solve();
}

/*
Để đánh dấu một bàn cờ 8x8 có các quân hợp lệ thì => dùng backtrack hoặc dp

Nếu như sắp từng hàng thì mình sẽ không cần quan tâm đến điều về hàng
Phải sắp sao cho con tiếp theo không nằm trên cột của mấy con trước dùng một cái trạng thái bitmask lưu lại cột nào đã được đánh dấu

Nhưng còn điều kiện đường chéo => đánh dấu các đường chéo riêng biệt đã được sử dụng. Làm thế nào để đánh dấu đường chéo

11 12 13 14 15 16 17 18
21 22 23 24 25 26 27 28
31 32 33 34 35 36 37 38
41 42 43 44 45 46 47 48
51 52 53 54 55 56 57 58
61 62 63 64 65 66 67 68
71 72 73 74 75 76 77 78
81 82 83 84 85 86 87 88

Nếu như lưu trạng thái cột và trạng thái của đường chéo là 30 => 38 => 2^38 => khá căng

Nếu như cộng vị trí i và j của các đường chéo lại thì

2 3 4 5 6 7 8 9
3 4 5 6 7 8 9 10
4 5 6 7 8 9 10 11
5 6 7 8 9 10 11 12
6 7 8 9 10 11 12 13
7 8 9 10 11 12 13 14
8 9 10 11 12 13 14 15
9 10 11 12 13 14 15 16

Ta nhận thấy nếu tại hàng i có các tổng i+j thì tại hàng i+1 có các tổng (i+1+j) => dịch tổng+1 => tạo ra các đường chéo mới => tạo ra hiệu ứng chéo ngang từ 2 -> 16

Nếu như ta trừ i - j thì ra cái gì



11 12 13 14 15 16 17 18
21 22 23 24 25 26 27 28
31 32 33 34 35 36 37 38
41 42 43 44 45 46 47 48
51 52 53 54 55 56 57 58
61 62 63 64 65 66 67 68
71 72 73 74 75 76 77 78
81 82 83 84 85 86 87 88

Nếu tại hàng i ta có kết quả j-i với mọi j thì ta có thể hiểu là j - (i + 1) = j - i - 1 => bị shift về bên trái => tạo ra hiệu ứng chéo ngược lại

0 1 2 3 4 5 6 7
-1 0 1 2 3 4 5 6
-2 -1 0 1 2 3 4 5
-3 -2 -1 0 1 2 3 4
-4 -3 -2 -1 0 1 2 3
-5 -4 -3 -2 -1 0 1 2
-6 -5 -4 -3 -2 -1 0 1
-7 -6 -5 -4 -3 -2 -1 0

Ta nên đánh dấu các đường chéo là từ 1->15 cho chéo phải là i+j-1 và cho chéo trái là j-i+8
Còn có những vật cản

Hàng 1 ta có 8 lựa chọn => 8 hàng => 8^8 = 1677216 => backtracking
Còn nếu ta dp bitmask thì ta có 2^(30 + 8) = 10^11 => TLE
*/