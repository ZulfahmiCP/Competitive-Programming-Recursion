#include <bits/stdc++.h>
using namespace std;
int main(){
    int tn;cin>> tn;
    while(tn--){
        int n, m, k;cin>> n >> m >> k;
        int res = n / m;
        if(n % m != 0) res++;
        cout << (n - res > k ? "YA\n" : "TIDAK\n");
    }
    return 0;
}