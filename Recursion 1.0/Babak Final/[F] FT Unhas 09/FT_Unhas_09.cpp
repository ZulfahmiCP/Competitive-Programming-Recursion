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
const int mod = MOD - 1;
const int INF = 2e9 + 7;
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;

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
using mll = mod_int<mod>;

struct SegTree {
    int N;
    vector<int> arr;
    vector<mll> A, D;

    SegTree(int n) : N(n), arr(N), A(4 * N, 0), D(4 * N, 0) {}

    void push(int x, int l, int r) {
        if(l == r) return;

        A[(x << 1) + 1] += A[x];
        A[(x << 1) + 2] += A[x] + D[x] * ((r - l) / 2 + 1);
        D[(x << 1) + 1] += D[x];
        D[(x << 1) + 2] += D[x];

        A[x] = D[x] = 0;
    }

    void update(int l, int r, ll a, ll d = 1) {
        modify(0, 0, N - 1, l, r, a, d);
    }

    void modify(int x, int l, int r, int ql, int qr, ll a, ll d) {
        push(x, l, r);

        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            A[x] += (a + d * (l - ql)), D[x] = d;
            push(x, l, r);
            return;
        }

        int m = (l + r) >> 1;

        modify((x << 1) + 1, l, m, ql, qr, a, d);
        modify((x << 1) + 2, m + 1, r, ql, qr, a, d);
    }

    int val(int j) {
        return process(0, 0, N - 1, j);
    }

    int process(int x, int l, int r, int j) {
        push(x, l, r);

        if(l == r)
            return (power(mint(9), A[x].val) * arr[l]).val;

        int m = (l + r) >> 1;
        
        return j <= m ? process((x << 1) + 1, l, m, j)
                      : process((x << 1) + 2, m + 1, r, j);
    }
};

struct HLD {
    int N, root, cnt;
    vector<vector<int>> adj, adj2;
    vector<int> value, pos, head;
    vector<int> depth, sub, parent;
    SegTree seg;
 
    HLD(int n) : N(n), cnt(0), sub(N, 1), pos(N), head(N), 
                 adj(N), depth(N), value(N), parent(N), seg(N) {}
 
    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build(int rt = 0) {
        root = rt;
        depth[root] = 0;
        parent[root] = 0;
        dfs_sub(root); 
        dfs_hld(root, 0);
    }
 
    int dfs_sub(int u) {
        eliminate(adj[u], parent[u]);

        for(const int &v : adj[u]){
            depth[v] = depth[u] + 1;
            parent[v] = u;
            sub[u] += dfs_sub(v);
        }

		sort(all(adj[u]), [&](int &a, int &b) {
			return sub[a] > sub[b];
		});

        return sub[u];
    }
 
    void dfs_hld(int u, bool heavy) {
        seg.arr[pos[u] = cnt++] = value[u];
        head[u] = heavy ? head[parent[u]] : u;
		bool heavy_child = 1;

		for(const int &v : adj[u]){
			dfs_hld(v, heavy_child);
			heavy_child = 0;
		}
    }

    int distance(int u, int v) {
        int d = 0;

        for(;head[u] != head[v]; u = parent[head[u]]){
            if(depth[head[u]] < depth[head[v]])
                swap(u, v);
            d += pos[u] - pos[head[u]] + 1;
        }

        if(depth[u] > depth[v])
            swap(u, v);

        d += pos[v] - pos[u] + 1;

        return d;
    }
 
    void update(int u, int v, ll a, ll d) {
        ll au = a, av = a + d * (distance(u, v) - 1);

        for(;head[u] != head[v];){
            if(depth[head[u]] >= depth[head[v]]){
                seg.update(pos[head[u]], pos[u], au + d * (pos[u] - pos[head[u]]), -d);
                au += d * (pos[u] - pos[head[u]] + 1);
                u = parent[head[u]];
            } else {
                seg.update(pos[head[v]], pos[v], av - d * (pos[v] - pos[head[v]]), d);
                av -= d * (pos[v] - pos[head[v]] + 1);
                v = parent[head[v]];
            }
        }

        if(depth[u] <= depth[v])
            seg.update(pos[u], pos[v], au, d);
        else 
            seg.update(pos[v], pos[u], av, -d);
    }
 
    int val(int u) {
        return seg.val(pos[u]);
    }
};  
int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    HLD tree(n);
 
    for(int &a : tree.value)
        cin >> a;

    for(int i = 1, u, v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    tree.build();
    debug(tree.head);
    debug(tree.sub);

    for(int i = 0, t,u,v,a,d; i < q; i++){
        cin >> t;

        if(t == 1){
            cin >> u >> v >> a >> d;
            u--, v--;
            tree.update(u, v, a, d);
        } else {
            cin >> u, u--;
            cout << tree.val(u) << '\n';
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
