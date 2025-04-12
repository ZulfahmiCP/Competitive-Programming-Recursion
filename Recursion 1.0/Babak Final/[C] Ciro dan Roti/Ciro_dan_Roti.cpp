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

using lint = __int128_t;

const int MOD = 1e9 + 9;
const ll mod = (1LL << 61) - 1;
const int INF = 2e9 + 7;
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;

void FastIO();

template<const ll &M = mod> struct mod_int {
    ll val;

    mod_int(ll v = 0) {if(v < 0) v = v % M + M; if(v >= M) v %= M; val = v;}

    friend mod_int power(mod_int a, ll b){mod_int c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend mod_int power(const mod_int &a, const mod_int b){return power(a, b.val);}
    friend mod_int inverse(const mod_int &a){return power(a, M - 2);}

    mod_int& operator+=(const mod_int &b){val += b.val; if (val >= M) val -= M; return *this;}
    mod_int& operator-=(const mod_int &b){val -= b.val; if (val < 0) val += M; return *this;}
    mod_int& operator*=(const mod_int &b){val = (lint)val * b.val % M; return *this;}
    mod_int& operator/=(const mod_int &b){return *this *= inverse(b);}
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

struct String {
    int N, K;
    string S;
    vector<mint> pref_hash, suff_hash;

    String() {}
    String(const string &s) : N(sz(s)), K(31), S(s), pref_hash(N), suff_hash(N) {
        char c = ('a' <= s[0] && s[0] <= 'z' ? 'a' : 'A');

        mint P = K;
        pref_hash[0] = s[0] - c + 1;
        for(int i = 1; i < N; i++, P *= K)
            pref_hash[i] = pref_hash[i - 1] + P * (s[i] - c + 1);

        suff_hash[N - 1] = s[N - 1] - c + 1;
        for(int i = N - 2; i >= 0; i--)
            suff_hash[i] = suff_hash[i + 1] * K + (s[i] - c + 1);
    }

    char& operator[](int i){return S[i];}
    int size(){return sz(S);}

    friend std::ostream& operator<<(std::ostream& os, const String &s){return os << s.S;}
    friend std::istream& operator>>(std::istream& is, String &s){is >> s.S; s = String(s.S); return is;}
};

int main(){
 
    FastIO();
    int N, K; cin >> N >> K;
    vector<string> S(N);
    vector<vector<ll>> pref(N, vector<ll>(100)), suff(N, vector<ll>(100));

    map<ll, int> who;
    
    // O(N * max(Ai) * log(N))
    for(int i = 0, cur = 0, m; i < N; i++){
        cin >> S[i];
        m = sz(S[i]);
        String s = S[i];
        
        for(int j = 0; j < m; j++){
            pref[i][j] = s.pref_hash[j].val;
            suff[i][j] = s.suff_hash[j].val;

            if(who.find(pref[i][j]) == who.end())
                who[pref[i][j]] = cur++;
            pref[i][j] = who[pref[i][j]];
            
            if(who.find(suff[i][j]) == who.end())
                who[suff[i][j]] = cur++;
            suff[i][j] = who[suff[i][j]];
        }
    }

    int M = sz(who);
    vector dp(K + 1, vector<int>(M + 1, INF));

    // O(N * K * max(|Ai|))
    for(int i = 0, m, x; i < N; i++){
        m = sz(S[i]);

        for(int j = K; j > 1; j--){
            x = INF;

            for(int k = 0; k < m; k++)
                x = min(x, dp[j - 1][pref[i][k]] + m - k - 1);
            
            for(int k = 0; k < m; k++)
                dp[j][suff[i][k]] = min(dp[j][suff[i][k]], x);
        }

        for(int k = 0; k < m; k++)
            dp[1][suff[i][k]] = min(dp[1][suff[i][k]], m);
    }
    
    for(int j = 1; j <= K; j++){
        int ans = *min_element(all(dp[j]));
        cout << (ans == INF ? -1 : ans) << '\n';
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
