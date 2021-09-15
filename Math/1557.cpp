#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
int K;

ll mobius[1010102];

//number of square-free numbers below n
ll count(ll n){
    ll ret=0;
    for(ll i = 1; i * i <= n; i++){
        ret+=(mobius[i]*(n/(i*i)));
    }
    return ret;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> K;
    for(int i = 1; i <= 1e6; i++){
        mobius[i]=1;
    }
    for(ll i = 2; i * i <= 1e6; i++){
        if(mobius[i]==1){
            for(ll j = i; j <= 1e6; j+=i){
                mobius[j]*=-i;
            }
            for(ll j = i * i; j <= 1e6; j += i*i){
                mobius[j]=0;
            }
        }
    }
    for(int i = 2; i <= 1e6; i++){
        if(mobius[i]==i)mobius[i]=1;
        else if(mobius[i]==-i)mobius[i]=-1;
        else if(mobius[i]<0)mobius[i]=1;
        else if(mobius[i]>0)mobius[i]=-1;
    }
    ll l = 0, r = 1e12;
    while(l+1<r){
        ll mid = (l+r)/2;
        ll tmp = count(mid);
        
        if(tmp<K)l=mid;
        else r = mid;
    }
    cout << r;
}