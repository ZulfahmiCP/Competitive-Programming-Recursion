#include <bits/stdc++.h>

using namespace std;
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
long long pangkat[60];
void solve() {
    long long n;
    cin >> n;
    for (int i = 1; i < 60; i++) {
        if (n+2 <= pangkat[i] && n+2 > pangkat[i-1]) {
            cout << i;
            return;
        }
    }
    cout << 60;
    return;
}
int main() {
    FastIO();
    pangkat[0] = 1;
    for (int i = 1; i < 60; i++) {
        pangkat[i] = 2 * pangkat[i-1]; 
    }
    int t;
    cin >> t;
    while(t--) {
        solve();
        cout << '\n';
    }
}