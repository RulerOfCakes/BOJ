#include <bits/stdc++.h>
using namespace std;
int N;
vector<int>v;
int cnt1[10100],cnt2[10100];
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    v=vector<int>(N+4);
    int ans=0;
    for(int i = 2; i < N+2; i++){
        cin >> v[i];
        ans+=3*v[i];
        if(cnt1[i-1]){
            int val=min(cnt1[i-1],v[i]);
            cnt2[i]=val;
            v[i]-=val;
            ans-=val;
        }
        if(cnt2[i-1]){
            int val=min(cnt2[i-1],v[i]);
            v[i]-=val;
            ans-=val;
        }
        
        cnt1[i]+=v[i];
    }
    
    cout << ans;
}