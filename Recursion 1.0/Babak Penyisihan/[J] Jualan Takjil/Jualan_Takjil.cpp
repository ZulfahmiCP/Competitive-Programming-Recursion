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

void FastIO();

struct SegTree {
    struct node {
        int l, r, mn, cnt, lz, left, right;

        node(int l = -1, int r = -1) : l(l), r(r), mn(0), cnt(r - l + 1), lz(0), left(-1), right(-1) {}
    };

    int N;
    vector<node> tree;
    
    SegTree(int n) : N(n), tree(1) {
        tree[0] = node(1, N);
    }

    void new_node(int x) {
        if(tree[x].l == tree[x].r) return;

        int m = (tree[x].l + tree[x].r) >> 1;

        if(tree[x].left == -1){
            tree[x].left = sz(tree);
            tree.pb(node(tree[x].l, m));
        }

        if(tree[x].right == -1){
            tree[x].right = sz(tree);
            tree.pb(node(m + 1, tree[x].r));
        }
    }

    void push(int x) {
        if(!tree[x].lz) return;

        tree[x].mn += tree[x].lz;

        if(tree[x].l != tree[x].r){
            new_node(x);
            tree[tree[x].left].lz += tree[x].lz;
            tree[tree[x].right].lz += tree[x].lz;
        }

        tree[x].lz = 0;
    }

    void pull(int x, int y, int z) {
        if(tree[y].mn > tree[z].mn)
            swap(y, z);
        tree[x].mn = tree[y].mn;
        tree[x].cnt = tree[y].cnt;
        if(tree[y].mn == tree[z].mn)
            tree[x].cnt += tree[z].cnt;
    }

    void update(int l, int r, int v) {
        modify(0, l, r, v);
    }   

    void modify(int x, int l, int r, int v) {
        push(x);

        if(r < tree[x].l || tree[x].r < l)
            return;

        if(l <= tree[x].l && tree[x].r <= r){
            tree[x].lz = v;
            push(x);
            return;
        }
        
        int m = (l + r) >> 1;
        
        new_node(x);
        modify(tree[x].left, l, r, v);
        modify(tree[x].right, l, r, v);

        pull(x, tree[x].left, tree[x].right);
    }

    int query() {
        return N - (tree[0].mn ? 0 : tree[0].cnt);
    }
};

int main(){
 
    FastIO();
    int n, m, q; cin >> n >> m >> q;
    vector<pair<int, int>> A(m);
    SegTree seg(n);

    for(auto &[a, b] : A) cin >> a >> b;
    
    for(int i = 0, t,j; i < q; i++){
        cin >> t >> j, j--;
        seg.update(A[j].fi, A[j].se, t == 1 ? 1 : -1);
        cout << seg.query() << '\n';
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
