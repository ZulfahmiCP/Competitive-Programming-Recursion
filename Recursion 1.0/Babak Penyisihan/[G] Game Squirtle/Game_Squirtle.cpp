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
const int MAX = 1e5 + 5;    

void FastIO();

template<const int &M = MOD> struct mod_int {
    int val;

    mod_int(ll v = 0) {if(v < 0) v = v % M + M; if(v >= M) v %= M; val = v;}

    friend mod_int power(mod_int a, ll b){mod_int c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend mod_int power(const mod_int &a, const mod_int b){return power(a, b.val);}
    friend mod_int inverse(const mod_int &a){return power(a, M - 2);}

    mod_int& operator+=(const mod_int &b){val += b.val; if (val >= M) val -= M; return *this;}
    mod_int& operator-=(const mod_int &b){val -= b.val; if (val < 0) val += M; return *this;}
    mod_int& operator*=(const mod_int &b){val = (ll)val * b.val % M; return *this;}
    mod_int& operator/=(const mod_int &b){return *this *= inverse(b);}
    mod_int& operator++(){val = val == M - 1 ? 0 : val + 1; return *this;}
    mod_int& operator--(){val = val == 0 ? M - 1 : val - 1; return *this;}
    mod_int operator++(int){mod_int a = *this; ++*this; return a;}
    mod_int operator--(int){mod_int a = *this; --*this; return a;}

    friend mod_int operator-(const mod_int &a){return 0 - a;}
    friend mod_int operator!(const mod_int &a){return a.val != 0;}
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
    
    friend ostream& operator<<(ostream& os, const mod_int &a){return os << a.val;}
    friend istream& operator>>(istream& is, mod_int &a){return is >> a.val; a = mod_int(a.val);}
};
using mint = mod_int<>;

struct DSU {
    int N;
    vector<int> parent, size;
    vector<mint> val;

    DSU(int n) : N(n), parent(N), size(N, 1), val(N, 1) {
        iota(all(parent), 0);
    }

    int find(int u) {
        if(u == parent[u]) return u;    
        int p = find(parent[u]);
        val[u] *= val[parent[u]];
        return parent[u] = p;
    }

    bool unite(int u, int v, int wu, int wv) {
        int pu = find(u), pv = find(v);
        
        if(pu == pv) return 0;

        if(size[pu] > size[pv]){
            swap(u, v);
            swap(pu, pv);
            swap(wu, wv);
        }

        val[pu] = (val[v] * wv) / (val[u] * wu);
        parent[pu] = pv;
        size[pv] += size[pu];

        return 1;
    }

    int query(int u, int v) {
        return (find(u) == find(v) ? (val[u] / val[v]).val : -1);
    }
};

ll pangkat(ll a, ll b) {
    ll c = 1;
    for(; b > 0; b >>= 1, a *= a)
        if(b & 1) c *= a;
    return c;
}

pair<ll, ll> max_pow(ll x) {
    for(ll b = 59; b > 1; b--){
        ll e = pow((double)x, 1.0 / b);
        for(ll a = max(2LL, e - 1); a <= e + 1; a++)
            if(pangkat(a, b) == x)
                return {a, b};
    }
    
    return {x, 1};
}

int main(){
 
    FastIO();
    int n,m,q; cin >> n >> m >> q;
    DSU dsu(n); 

    for(ll i = 0, t, x, y, u, v; i < m + q; i++){
        cin >> t;

        if(t == 1){
            cin >> x >> y >> u >> v, u--, v--;

            auto px = max_pow(x);
            auto py = max_pow(y);

            dsu.unite(u, v, px.se, py.se);
        } else {
            cin >> u >> v, u--, v--;
            cout << dsu.query(u, v) << '\n';;
        }
    }

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
