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

struct node {
    int val, prior, size;
    bool rev, inc, dec;
    int first, last;
    node *l, *r;

    node(int v) : val(v), first(v), last(v), rev(0), inc(1), dec(1), prior(rand()), size(1), l(NULL), r(NULL) {}
};

struct Treap {
    node *root;

    int size(node *x) { return x ? x->size : 0; }
    int first(node *x, int v) { return x ? x->first : v; }
    int last(node *x, int v) { return x ? x->last : v; }
    bool inc(node *x) { return x ? x->inc : 1; }
    bool dec(node *x) { return x ? x->dec : 1; }

    void insert(int v) {
        merge(root, root, new node(v));
    }

    void pull(node *x) {
        if(!x) return;
        push(x->l), push(x->r);
        x->size = size(x->l) + size(x->r) + 1;
        int v = x->val;
        x->first = first(x->l, v), x->last = last(x->r, v);
        x->inc = inc(x->l) && inc(x->r) && last(x->l, v) <= v && v <= first(x->r, v);
        x->dec = dec(x->l) && dec(x->r) && last(x->l, v) >= v && v >= first(x->r, v);
    }

    void push(node *x) {
        if(!x || !x->rev) return;
        swap(x->inc, x->dec);
        swap(x->first, x->last);
        swap(x->l, x->r);
        if(x->l) x->l->rev ^= true;
        if(x->r) x->r->rev ^= true;
        x->rev = 0;
    }
    
    void merge(node *&x, node *l, node *r) {
        if(!l || !r){
            x = l ? l : r;
            return;
        }
        
        push(l), push(r);

        if(l->prior < r->prior){
            merge(l->r, l->r, r);
            x = l;
        } else {
            merge(r->l, l, r->l);
            x = r;
        }
        
        pull(x);
    }

    void split(node *x, node *&l, node *&r, int val) {
        if(!x){
            l = r = NULL;
            return;
        }

        push(x);

        if(size(x->l) < val){
            split(x->r, x->r, r, val - size(x->l) - 1);
            l = x;
        } else {
            split(x->l, l, x->l, val);
            r = x;
        }

        pull(x);
    }

    node *a, *b, *c, *d;

    void reverse(int l, int r) {
        split(root, a, b, l);  
        split(b, b, c, r - l + 1);
        if(b) b->rev ^= true;
        merge(root, a, b);
        merge(root, root, c);
    }

    bool query(int l, int r, bool increase) {
        split(root, a, b, l);  
        split(b, b, c, r - l + 1);
        bool ans = increase ? inc(b) : dec(b);
        merge(root, a, b);
        merge(root, root, c);
        return ans;
    }
} treap;

int main(){
 
    FastIO();
    int n, q; cin >> n >> q;
    
    for(int i = 0, x; i < n; i++){
        cin >> x;
        treap.insert(x);
    }

    for(int i = 0, t,l,r; i < q; i++){
        cin >> t >> l >> r, l--, r--;

        if(t == 1)
            treap.reverse(l, r);
        else if(t == 2) 
            cout << (treap.query(l, r, 1) ? "IYA" : "TIDAK") << '\n';
        else 
            cout << (treap.query(l, r, 0) ? "IYA" : "TIDAK") << '\n';
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
