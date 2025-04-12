#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    vector<long long> a(n);
    long long total = 0;
    long long maksimum = -1;
    bool valid = true;
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
        if (maksimum < a[i]) {
            maksimum = a[i];
        }
        if (total > 1e18 + m) {
            valid = false;
        }
    }
    if (n == 1) {
        cout << "YA";
        return 0;
    }
    if (n == 2) {
        if (m >= min(a[0], a[1])) {
            cout << "YA";
        } else {
            cout << "TIDAK";
        }
        return 0;
    }
    if (!valid) {
        cout << "TIDAK";
        return 0;
    }
    map<long long, long long> b, c;
    for (long long i = 0; i < n; i++) {
        long long d = a[i] % n;
        if (b.find(d) == b.end()) {
            b[d] = 0;
            c[d] = a[i];
        }
        b[d]++;
    }
    if (b.size() == 1) {
        long long m2 = total - maksimum;
        if (m2 <= m) {
            cout << "YA";
        } else {
            cout << "TIDAK";
        }
        return 0;
    }
    if (b.size() == 2) {
        long long dapat = -1;
        for (auto k : b) {
            if (k.second == 1) {
                dapat = k.first;
                break;
            }
        }
        if (dapat == -1) {
            cout << "TIDAK";
            return 0;
        } 
        long long m2 = total - c[dapat];
        if (m2 <= m) {
            cout << "YA";
        } else {
            cout << "TIDAK";
        }
        return 0;
    }
    cout << "TIDAK";
    return 0;
}