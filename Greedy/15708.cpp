#include <bits/stdc++.h>
using namespace std;
int T,N,P,ans;long long sm;
int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> N >> T >> P;
    priority_queue<int>pq;
    for(int i= 0; i < N; i++){
        int a;cin>>a;
        pq.push(a);sm+=a;
        long long ct=T-(long long)i*P;
        while(!pq.empty()&&sm>ct){
            sm-=pq.top();
            pq.pop();
        };
        ans=max(ans,(int)pq.size());
    }
    cout<<ans;
}