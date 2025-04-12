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

template<typename B> void flip(B &n, int i){n ^= ((B)1 << i);}
template<typename B> void toggle(B &n, int i){n |= ((B)1 << i);} 
template<typename B> void clear(B &n, int i){n &= ~((B)1 << i);}
template<typename B> void change_bit(B &n, int i, bool b){b ? toggle(n, i) : clear(n, i);}
template<typename B> bool is_set(B n, int i){return (n >> i) & 1;}
template<typename B> bool is_pow_two(B n){return n && (!(n & (n - 1)));}
template<typename B> int get(B n, int i){return (n >> i) & 1;}
template<typename B> int one_cnt(B n){return __builtin_popcount(n);}
template<typename B> int high(B n){return n == 0 ? -1 : 31 - __builtin_clz(n);}
template<typename B> int low(B n){return n == 0 ? -1 : __builtin_ctz(n);}
template<typename B> int max_even(B n){return n & 1 ? 0 : 1 + max_even(n >> 1);}
template<typename B> int max_odd(B n){while(!(n & 1) && n > 0) n >>= 1; return n;}
template<typename B> ll pow_two(B n){return (1LL << n);}

int main(){
 
    FastIO();
    int n, m; cin >> n >> m;
    ll ans = 0, k = 1 << n;
    vector<pair<ll, ll>> A(n);

    for(int i = 0; i < n; i++){
        vector<int> B(m);

        for(int j = 0; j < m; j++){
            cin >> B[j];
            if(j > 0)
                ans += 1LL * B[j] * B[j - 1];
        }

        A[i] = {B[0], B[m - 1]};
    }

    if(n == 1){
        cout << ans + A[0].fi * A[0].se << '\n';
        return 0;
    }

    vector<vector<ll>> dp(k, vector<ll>(n, 0));

    for(int i = 1; i < n; i++)
        dp[(1 << i) | 1][i] = A[0].fi * A[i].se + A[0].se * A[i].fi;

    for(int mask = 3, prev; mask < k; mask += 2){
        if(one_cnt(mask) <= 2) continue;
        
        for(int i = 0; i < n; i++){
            if(!get(mask, i)) continue;
            
            prev = mask;
            flip(prev, i);
        
            for(int j = 0; j < n; j++)
                if(get(prev, j))
                    dp[mask][i] = max(dp[mask][i], dp[prev][j] + A[0].fi * (A[i].se - A[j].se) + A[j].se * A[i].fi);
        }
    }
    
    cout << ans + (*max_element(1 + all(dp[k - 1]))) << '\n';

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
