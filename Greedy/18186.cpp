#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N,B,C;
vector<int>v;
int cnt1[1010000],cnt2[1010000];
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> B >> C;
    if(C>=B){
        ll ans=0;
        for(int i = 0; i < N; i++){
            ll a;
            cin>> a;
            ans+=a*B;
        }
        cout << ans;
        return 0;
    }
    ll diff=B-C;
    v=vector<int>(N+4);
    ll ans=0;
    for(int i = 2; i < N+2; i++){
        cin >> v[i];
        ans+=B*(ll)v[i];
        if(cnt1[i-1]){
            int val=min(cnt1[i-1],v[i]);
            cnt2[i]=val;
            v[i]-=val;
            ans-=diff*val;
        }
        if(cnt2[i-1]){
            int val=min(cnt2[i-1],v[i]);
            v[i]-=val;
            ans-=diff*val;
        }
        
        cnt1[i]+=v[i];
    }
    
    cout << ans;
}