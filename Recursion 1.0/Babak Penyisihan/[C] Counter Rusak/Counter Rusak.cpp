#include <bits/stdc++.h>

using namespace std;

int main() {
    long long t;
    cin >> t;
    long long hasil[t];
    long long c8[] = {0, 1, 2, 3, 3, 4, 5, 6, 6, 7};
    long long p8[20];
    p8[0] = 1;
    for (long long i = 1; i < 20; i++) {
        p8[i] = p8[i-1] * 8;
    }
    for (long long p = 0; p < t; p++) {
        string k;
        cin >> k;
        long long digit[k.size()];
        for (long long i = 0; i < k.size(); i++) {
            digit[i] = c8[k[i] - '0'];
        }
        hasil[p] = 0;
        for (long long i = 0; i < k.size(); i++) {
            hasil[p] += digit[i] * p8[k.size() - 1 - i];
        }
    }
    for (long long i = 0; i < t; i++) {
        cout << hasil[i] << endl;
    }
}