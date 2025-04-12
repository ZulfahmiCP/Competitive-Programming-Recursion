#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const ll MOD = 1e9+7;

int T;
ll N, A;

ll expo(ll x,ll y=MOD-2) {
	if (y == 0) return 1;
	x %= MOD;
	ll r = expo(x*x,y/2);
	if (y%2) r = r*x%MOD;
	return r;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> N;
		A = expo(6,N+1);
		if (N % 2 == 1) {
			cout << (A+6)%MOD*expo((2*A+5)%MOD)%MOD << "\n";
		}
		else {
			cout << (A-6 + MOD)%MOD*expo((2*A-5 + MOD)%MOD)%MOD << "\n";
		}
	}
}