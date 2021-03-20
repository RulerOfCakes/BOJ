#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
int N, M, K;

ll sol(ll a, ll b, ll c){
    //a^b)%c
    if(b==0)return 1;
    if(b % 2 == 1){
        return (a*sol(a, b-1, c)%c);
    }
    else{
        ll result = sol(a, b/2, c);
        result %= c;
        return (result*result)%c;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll a, b, c;
    cin >> a >> b >> c;
    cout << sol(a, b, c);
}