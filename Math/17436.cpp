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
    ll N,M;
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M;vector<ll> pv;
    for(int i = 0; i  <N; i++){
        ll a;cin>>a;pv.push_back(a);
    }
    cout << multiples(pv,0,1,M);
}