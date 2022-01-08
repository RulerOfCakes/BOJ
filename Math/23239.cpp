#include <bits/stdc++.h>
using namespace std;
using pi=pair<int,int>;
using ll = long long;
ll W,H,L;
//1 quartercircle worth of points not on the axixs
ll cntpts(ll r){
    ll ret=0;
    ll j=r-1;
    for(ll i = 1; i < r; i++){
        while(i*i+j*j>r*r)j--;
        ret+=j;
    }
    return ret;
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >>W>>H>>L;
    ll ans=2*L+3*cntpts(L);

    ans+=cntpts(max(L-H,0LL))+max(L-H,0LL);
    ans+=cntpts(max(L-W,0LL))+max(L-W,0LL);
    if(L-H>W&&L-W>H){
        //overlap
        ll j = L-H-1;
        for(ll i = H+1; i < L-W; i++){
            while(((i-H)*(i-H)+j*j>(L-H)*(L-H))||((j-W)*(j-W)+i*i>(L-W)*(L-W)))j--;
            ans-=(j-W);
        }
    }
    cout << ans;
}