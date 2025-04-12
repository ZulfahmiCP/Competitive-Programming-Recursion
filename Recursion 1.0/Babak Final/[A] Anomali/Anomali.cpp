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
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;
const int LOG = 30;

void FastIO();

template<const int &M = MOD> struct mod_int {
    int val;

    mod_int(ll v = 0) {if(v < 0) v = v % M + M; if(v >= M) v %= M; val = v;}

    friend mod_int power(mod_int a, ll b){mod_int c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend mod_int power(const mod_int &a, const mod_int b){return power(a, b.val);}
    friend mod_int inv(const mod_int &a){return power(a, M - 2);}

    mod_int& operator+=(const mod_int &b){val += b.val; if (val >= M) val -= M; return *this;}
    mod_int& operator-=(const mod_int &b){val -= b.val; if (val < 0) val += M; return *this;}
    mod_int& operator*=(const mod_int &b){val = (ll)val * b.val % M; return *this;}
    mod_int& operator/=(const mod_int &b){return *this *= inv(b);}
    mod_int& operator++(){val = val == M - 1 ? 0 : val + 1; return *this;}
    mod_int& operator--(){val = val == 0 ? M - 1 : val - 1; return *this;}
    mod_int operator++(int){mod_int a = *this; ++*this; return a;}
    mod_int operator--(int){mod_int a = *this; --*this; return a;}

    friend mod_int operator!(const mod_int &a){return a.val != 0;}
    friend mod_int operator-(const mod_int &a){return 0 - a;}
    friend mod_int operator+(const mod_int &a, const mod_int &b){return mod_int(a) += b;}
    friend mod_int operator-(const mod_int &a, const mod_int &b){return mod_int(a) -= b;}
    friend mod_int operator*(const mod_int &a, const mod_int &b){return mod_int(a) *= b;}
    friend mod_int operator/(const mod_int &a, const mod_int &b){return mod_int(a) /= b;}
    
    friend bool operator==(const mod_int &a, const mod_int &b){return a.val == b.val;}
    friend bool operator!=(const mod_int &a, const mod_int &b){return a.val != b.val;}
    friend bool operator>=(const mod_int &a, const mod_int &b){return a.val >= b.val;}
    friend bool operator<=(const mod_int &a, const mod_int &b){return a.val <= b.val;}
    friend bool operator>(const mod_int &a, const mod_int &b){return a.val > b.val;}
    friend bool operator<(const mod_int &a, const mod_int &b){return a.val < b.val;}
    
    friend std::ostream& operator<<(std::ostream& os, const mod_int &a){return os << a.val;}
    friend std::istream& operator>>(std::istream& is, mod_int &a){return is >> a.val; a = mod_int(a.val);}
};
using mint = mod_int<>;

struct Tree {
    int N;
    vector<vector<int>> adj;
    vector<vector<mint>> dp;
    vector<int> sub;

    Tree(int n) : N(n), adj(N), sub(N, 0), dp(N, vector<mint>(LOG, 0)) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build() {
        dfs(0, -1);
    }

    void dfs(int u, int p) {
        for(int &v : adj[u]) if(v != p){
            dfs(v, u);
            sub[u] += sub[v] + 1;
        }

        if(u && sz(adj[u]) == 1){
            for(int x = 0; x < LOG; x++)
                dp[u][x] = 1;
            return;
        }

        for(int a = 0; a < LOG; a++){
            // if A[u] = a
            dp[u][a] = power(mint(a + 1), sub[u]);

            // if A[u] != a
            mint s = 1;

            for(int &v : adj[u])
                if(v != p)
                    s *= dp[v][a];

            dp[u][a] += s * a;
        }
    }
};

vector<pair<int, int>> factor(int n) {
    vector<pair<int, int>> fac;

    for(int i = 2; i * i <= n; i++){
        if(n % i) continue;
        fac.pb({i, 0});
        while(!(n % i))
            n /= i, fac.back().se++;
    }

    if(n > 1) fac.pb({n, 1});
    return fac;
}

int main(){
 
    FastIO();
    int n, m; cin >> n >> m;
    Tree tree(n);

    for(int i = 1, u,v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    tree.build();

    mint ans = 1;

    for(auto [p, e] : factor(m))
        ans *= tree.dp[0][e];
    
    cout << ans << '\n';

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
