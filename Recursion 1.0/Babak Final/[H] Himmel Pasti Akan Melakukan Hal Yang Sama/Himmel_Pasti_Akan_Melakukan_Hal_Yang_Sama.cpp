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
const int MAX = 1e9;

void FastIO();

int n, k;
vector<ll> cur;
vector<vector<ll>> res;

ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}

ll lcm(vector<ll> X) {
    ll kpk = 1;
    for(ll &x : X) kpk = lcm(kpk, x);
    return kpk;
}

void dfs(ll m, ll x, ll y, ll z) {
    ll a = x * z, b = z * y - x;
    if(b <= 0 || z >= MAX) return;

    if(m == 2){
        if(a % b) return;

        cur.pb(a / b);
        x = 1;

        for(ll &p : cur) x = lcm(x, p);

        vector<ll> B(k);
        for(ll i = 0; i < k; i++)
            B[i] = x / cur[i];

        reverse(all(B));
        
        if(B.back() <= MAX && lcm(B) == accumulate(all(B), 0))
            res.pb(B);

        cur.ppb();
        return; 
    }

    ll s = max(cur.back() * b, (a + 1) + ((b - (a + 1) % b) % b));
    for(ll i = s; i <= a * (m - 1); i += b){
        cur.pb(i / b);
        dfs(m - 1, a, b, i / b);
        cur.ppb();
    }        
}

int main(){
 
    FastIO();
    cin >> n >> k;

    if(k == 1){
        cout << n << '\n';
        return 0;
    } else if(k == 2) {
        cout << "0\n";
        return 0;
    }

    for(int i = 2; i <= k; i++){
        cur.pb(i);
        dfs(k, 1, 1, i);
        cur.ppb();
    }
    
    make_unique(res);

    ll m, ans = 0;
    vector<int> A(n);
    map<int, int> occ;

    for(int &a : A) cin >> a;
    sort(all(A));

    for(int &a : A){
        for(auto &x : res){
            if(a % x[k - 1]) continue;
            a /= x[k - 1], m = 1;

            for(int j = 0, l = 1; j < k - 1; j++){
                m *= max(0, occ[x[j] * a] - l + 1);
                m /= l;
                
                if(j < k - 1 && x[j] == x[j + 1])
                    l++;
                else 
                    l = 1;
            }

            ans += m;

            a *= x[k - 1];
        }

        occ[a]++;
    }

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
