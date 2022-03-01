#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll multiples(vector<ll>& pv, int i, ll cx, ll bound){
    if(i==pv.size()||pv[i]*cx>bound)return 0;
    ll ret = (bound/pv[i])/cx;
    ret+=multiples(pv,i+1,cx,bound);
    ret-=multiples(pv,i+1,pv[i]*cx,bound);
    return ret;
}

int main(){
    ll N;
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;

    ll ans = 0;
    vector<ll> pv;
    ll i;
    for(i = 11; i <= N; i=i*10+1){
        bool falsey=0;
        for(ll x : pv){
            if(!(i%x)){
                falsey=1;
                break;
            }
        }
        if(falsey)continue;
        pv.push_back(i);
    }
    cout << multiples(pv,0,1,N);
}