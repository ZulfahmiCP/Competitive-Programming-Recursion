#include <bits/stdc++.h>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define Int unsigned int 
#define Long unsigned long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& val);
template<typename T, typename... Args>void prd(const T& val, Args... args);
template<typename... Args>void debug(Args... args);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct SegTree {
    int N;
    vector<int> tree;

    SegTree(int n) : N(n), tree(4 * N, 0) {}

    void update(int j, int v){
        modify(0, 0, N - 1, j, v);
    }

    void modify(int x, int l, int r, int j, int v) {
        if(l == r){
            tree[x] = v;
            return;
        }

        int m = (l + r) >> 1;
        
        j <= m ? modify(2 * x + 1, l, m, j, v)
               : modify(2 * x + 2, m + 1, r, j, v);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }

    int calc(int l, int r) {
        return l <= r ? process(0, 0, N - 1, l, r) : 0;
    }

    int process(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql)
            return 0;

        if(ql <= l && r <= qr)
            return tree[x];
        
        int m = (l + r) >> 1;
        
        return max(process(2 * x + 1, l, m, ql, qr), 
                   process(2 * x + 2, m + 1, r, ql, qr));
    }
};

int main(){
 
    FastIO();
    int n, k; cin >> n >> k;
    vector<pair<int, int>> A(n);
    vector<vector<pair<int, int>>> bad(n);
    vector<int> pos(n);
    SegTree dp(n);

    for(int i = 0; i < n; i++){
        cin >> A[i].fi;
        A[i].se = i;
    }

    for(int p = 0, i, j; p < k; p++){
        cin >> i >> j, i--, j--;
        bad[i].pb({j, 0});
    }

    sort(all(A), [&](pair<int, int> &a, pair<int, int> &b) {
        return a.fi == b.fi ? a.se < b.se : a.fi > b.fi;
    });

    for(int i = 0; i < n; i++)
        pos[A[i].se] = i;

    for(int i = n - 1; i >= 0; i--){
        for(auto &[p, v] : bad[i]){
            v = dp.calc(pos[p], pos[p]);
            dp.update(pos[p], 0);
        }

        dp.update(pos[i], dp.calc(0, pos[i] - 1) + 1);

        for(auto &[p, v] : bad[i])
            dp.update(pos[p], v);
    }

    for(int i = 0; i < n; i++)
        cout << dp.calc(pos[i], pos[i]) << " \n"[i == n - 1];

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
