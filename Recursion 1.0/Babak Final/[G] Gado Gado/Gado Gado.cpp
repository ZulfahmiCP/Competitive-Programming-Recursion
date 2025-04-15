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

struct Matrix {
    int N, M;
    vector<vector<mint>> Mat;

    Matrix() {}
    Matrix(const vector<vector<int>>& mat) : N(sz(mat)), M(sz(mat[0])) {
        Mat.resize(N, vector<mint>(M));
        for(int i = 0; i < N; i++)  
            for(int j = 0; j < M; j++)
                Mat[i][j] = mint(mat[i][j]);
    }

    Matrix(int n, int m, int x = 0) : N(n), M(m), Mat(N, vector<mint>(M, x)) {}

    Matrix& operator*=(const Matrix& A) {
        Matrix prod(N, A.M); assert(M == A.N);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < A.M; j++)
                for(int k = 0; k < M; k++)
                    prod[i][j] += Mat[i][k] * A.Mat[k][j];
        return *this = prod;
    }

    friend Matrix operator*(const Matrix &a, const Matrix &b) { return Matrix(a) *= b; }

    friend Matrix power(Matrix A, ll B) {
        Matrix C(A.N, A.M); assert(A.N == A.M);
        
        for(int i = 0; i < A.N; i++)
            C[i][i] = 1;

        for(; B > 0; A *= A, B >>= 1)
            if(B & 1) C *= A;

        return C;
    }

    vector<mint>& operator[](int i) {
        return Mat[i];
    }
};

// if the first sequence start with F[0] then n++
vector<mint> result(const Matrix &A, const Matrix &B, int n, ll k) {
    auto res = power(A, k) * B;
    vector<mint> ans(n);

    for(int i = 0; i < n; i++)
        ans[i] = res.Mat[i][0];
    
    return ans;
}

int main(){
 
    FastIO();
    ll n, q; cin >> n >> q;
    vector<vector<int>> sum(n, vector<int>(n, 0));
    vector<int> A(n);

    for(int &a : A) cin >> a;
        
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++)
            sum[i][j] = n - i;
        for(int j = i; j < n; j++)
            sum[i][j] = n - j;
    }
        
    vector<Matrix> base(60);

    base[0] = Matrix(sum);
    for(int i = 1; i < 60; i++)
        base[i] = base[i - 1] * base[i - 1];

    for(ll l = 0, p,x,k; l < q; l++){
        cin >> p >> x >> k;
        vector<mint> dp(n);

        A[--p] = x;

        for(int i = 0; i < n; i++)
            dp[i] = A[i];

        for(int bit = 0; (1LL << bit) <= k; bit++){
            if(!(k & (1LL << bit))) continue;

            vector<mint> new_dp(n);

            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    new_dp[i] += dp[j] * base[bit].Mat[i][j];

            dp = new_dp;
        }

        for(int i = 0; i < n; i++)
            cout << dp[i] << " \n"[i == n - 1];
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
