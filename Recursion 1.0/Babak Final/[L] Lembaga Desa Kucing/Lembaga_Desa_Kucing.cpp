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
template<typename T>void debug(const multiset<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;
const int LOG = 26;

void FastIO();

struct node {
    bool whole;
    int pref, suff, sum, lz;
    ll val;
    node(bool a = 1, int b = 0, int c = 0, int d = 0, ll e = 0, int f = -1) :
    whole(a), pref(b), suff(c), sum(d), val(e), lz(f) {}
};  

struct SegTree {
    int N;
    vector<int> arr;
    vector<array<node, LOG>> tree;

    SegTree() {}
    SegTree(int n) : N(n), arr(N), tree(4 * N) {}

    node pull(node a, node b) {
        return {
            (a.whole && b.whole),
            a.pref + (a.whole ? b.pref : 0),
            b.suff + (b.whole ? a.suff : 0),
            max({a.sum, b.sum, a.suff + b.pref}),
            a.val + b.val + 2LL * a.suff * b.pref
        };  
    }

    void build(int x, int l, int r) {
        if(l == r){
            for(int c = 0; c < 26; c++)
                tree[x][c] = {0, 0, 0, 0, 0, -1};
            tree[x][arr[l]] = {1, 1, 1, 1, 1, -1};
            return;
        }

        int m = (l + r) >> 1;

        build((x << 1), l, m);
        build((x << 1) | 1, m + 1, r);

        for(int c = 0; c < LOG; c++)
            tree[x][c] = pull(tree[(x << 1)][c], tree[(x << 1) | 1][c]);
    }

    void push(int x, int l, int r) {
        for(int c = 0; c < LOG; c++){
            if(tree[x][c].lz == -1)
                return;

            if(l != r){
                tree[(x << 1)][c].lz = tree[x][c].lz;
                tree[(x << 1) | 1][c].lz = tree[x][c].lz;
            }

            ll y = (r - l + 1) * tree[x][c].lz;
            tree[x][c] = {y, y, y, y, y * y, -1};
        }
    }

    void update(int l, int r, int j) {
        modify(1, 0, N - 1, l, r, j);
    }

    void modify(int x, int l, int r, int ql, int qr, int j) {
        push(x, l, r);

        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            for(int c = 0; c < LOG; c++)
                tree[x][c].lz = j == c;
            push(x, l, r);
            return;
        }

        int m = (l + r) >> 1;

        modify((x << 1), l, m, ql, qr, j);
        modify((x << 1) | 1, m + 1, r, ql, qr, j);

        for(int c = 0; c < LOG; c++)
            tree[x][c] = pull(tree[(x << 1)][c], tree[(x << 1) | 1][c]);
    }

    int mxp() {
        int mx = 0;
        for(int c = 0; c < LOG; c++)
            mx = max(mx, tree[1][c].sum);
        return mx;
    }

    node calc(int l, int r, int j) {
        return process(1, 0, N - 1, l, r, j);
    }

    node process(int x, int l, int r, int ql, int qr, int j) {
        push(x, l, r);

        if(qr < l || r < ql)
            return node();

        if(ql <= l && r <= qr)
            return tree[x][j];

        int m = (l + r) >> 1;

        return pull(process((x << 1), l, m, ql, qr, j),
                    process((x << 1) | 1, m + 1, r, ql, qr, j));
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    string s; cin >> s;
    SegTree seg(n);

    for(int i = 0; i < n; i++)
        seg.arr[i] = s[i] - 'A';

    seg.build(1, 0, n - 1);

    for(ll i = 0, t,l,r,power; i < q; i++){
        char c;
        cin >> t;
        
        if(t == 1){
            cin >> l >> r >> c;
            l--, r--;
            seg.update(l, r, c - 'A');
        } else if(t == 2) {
            cin >> l >> r, l--, r--;
            power = 0;

            for(int j = 0; j < LOG; j++){
                node x = seg.calc(l, r, j);
                power += x.val;

                if(x.pref && l > 0)
                    power += (1LL * x.pref * seg.calc(0, l - 1, j).suff);
                if(x.suff && r < n - 1)
                    power += (1LL * seg.calc(r + 1, n - 1, j).pref * x.suff);
            }

            cout << power << '\n';
        } else {
            cout << seg.mxp() << '\n';
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
template<typename T> void debug(const multiset<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
