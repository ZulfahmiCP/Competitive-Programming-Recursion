#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
 
    int n,k; cin >> n >> k;
    vector<int> A(n);
    bool even = false;

    for(int &a : A){
        cin >> a;
        if(a % 2 == 0) even = true;
    }

    if(even == false){
        k--;
        (*min_element(A.begin(), A.end()))++;
    }

    auto good = [&](int x) -> bool {
        ll sum = 0;

        for(int &a : A)
            sum += max(0, (x - a + 1) / 2);
        
        return sum <= k;
    };

    ll l = *min_element(A.begin(), A.end()), r = 2e9 + 5, m;
    while(r - l > 1){
        m = (l + r) / 2;
        good(m) ? l = m : r = m;
    }

    cout << l << '\n';
    priority_queue<int, vector<int>, greater<int>> arr;

    for(int &a : A){
        if(a < l){
            k -= (l - a + 1) / 2;
            a = l + ((l - a) & 1);
        }
        arr.push(a);
    }

    for(int i = 0; i < k; i++){
        int temp = arr.top() + 2;
        arr.pop();
        arr.push(temp);
    }

    while(arr.empty() == false){
        cout << arr.top() << ' ';
        arr.pop();  
    }

    return 0;
}
 