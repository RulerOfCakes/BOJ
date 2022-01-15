#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N;
    ll K;
    cin >> N >> K;
    ll l=1,r=N*N,ans=l+r>>1;
    while(l<=r){
        ll cnt1=0,mid=l+r>>1;
        for(ll i = 1; i <= N; i++){
            cnt1+=min(mid/i,N);
        }
        
        if(cnt1>=K){
            r=mid-1;
            ans=mid;
        }
        else{
            l=mid+1;
        }
    }
    cout << ans;
}