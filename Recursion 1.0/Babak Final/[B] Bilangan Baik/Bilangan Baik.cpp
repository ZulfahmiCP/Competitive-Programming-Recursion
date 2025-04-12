#include <bits/stdc++.h>

using namespace std;

long long mod = 1e9 + 7;
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}

long long pangkat(long long n, long long k) {
    long long basis = n;
    long long hasil = 1;
    while (k > 0) {
        if (k % 2 == 1) {
            hasil = hasil * basis;
        }
        k /= 2;
        basis = basis * basis;
    }
    return hasil;
}

int main() {
    FastIO();
    bool is_prima[1000000];
    for (long long i = 0; i < 1e6; i++) {
        is_prima[i] = true;
    }
    for (long long i = 2; i < 1e6; i++) {
        if (is_prima[i]) {
            for (long long j = i*2; j < 1e6; j+=i) {
                is_prima[j] = false;
            }
        }
    }
    vector<long long> l_prima;
    for (long long i = 2; i < 1e6; i++) {
        if (is_prima[i] && i != 37) {
            l_prima.push_back(i);
        }
    }
    long long p_sum[l_prima.size()];
    p_sum[0] = 0;
    p_sum[1] = 3;
    for (long long i = 2; i < l_prima.size(); i++) {
        p_sum[i] = (p_sum[i-1] + l_prima[i]) % mod;
    }
    long long kali = pangkat(2, 36) * 37;
    long long t;
    cin >> t;
    long long hasil[t];
    for (long long p = 0; p < t; p++) {
        long long k;
        cin >> k;
        if (k <= kali*3) {
            hasil[p] = 0;
            continue;
        }
        long long l = k / kali;
        auto m2 = lower_bound(l_prima.begin(), l_prima.end(), l);
        long long m = m2 - l_prima.begin();
        if (l_prima[m] * kali >= k) {
            m--;
        }
        hasil[p] = (kali % mod) * p_sum[m];
        hasil[p] = hasil[p] % mod;
        if (k > 3480847655108608) {
            hasil[p] += 3480847655108608;
            hasil[p] = hasil[p] % mod;
        }
    }
    for (long long i = 0; i < t; i++) {
        cout << hasil[i] << '\n';
    }
}