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

int main(){
 
	FastIO();
	int n, q; cin >> n >> q;
	string s; cin >> s;
	set<int> index;
	multiset<int> power;

	index.insert(-1);
	power.insert(0);

	for(int i = 0, j = 0; i < n; i = ++j){
		while(j + 1 < n && s[i] == s[j + 1])
			j++;
		index.insert(j);
		power.insert(j - i + 1);
	}

	auto cnt = [&](int i) -> int {
		auto r = index.lower_bound(i);
		auto l = r; l--;
		return *r - *l;
	};	

	auto cut = [&](int i) -> void {
		auto r = index.lower_bound(i);
		auto l = r; l--;
		power.erase(power.find(*r - *l));
		power.insert(*r - i);
		power.insert(i - *l);
		index.insert(i);
	};

	auto join = [&](int i) -> void {
		index.erase(i);
		auto r = index.lower_bound(i);
		auto l = r; l--;
		power.erase(power.find(*r - i));
		power.erase(power.find(i - *l));
		power.insert(*r - *l);
	};

	for(int i = 0, t,j; i < q; i++){
		cin >> t;

		if(t == 1){
			cin >> j, j--;

			if(j < n - 1 && s[j] == s[j + 1])
				cut(j);
			if(j > 0 && s[j] == s[j - 1])
				cut(j - 1);
			
			cin >> s[j];

			if(j < n - 1 && s[j] == s[j + 1])
				join(j);
			if(j > 0 && s[j] == s[j - 1])
				join(j - 1);
		} else if(t == 2) {
			cin >> j, j--;
			cout << cnt(j) << '\n';
		} else {
			cout << *power.rbegin() << '\n';
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
