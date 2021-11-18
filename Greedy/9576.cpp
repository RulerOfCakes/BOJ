#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int N,M,T;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> T;
    while(T--){
        cin >> N >> M;
        priority_queue<pi,vector<pi>,greater<pi>> pq;
        vector<bool>v(N+1);
        for(int i = 0 ; i < M; i++){
            int a,b;
            cin >> a >> b;
            pq.push({b,a});
        }int ans=0;
        while(!pq.empty()){
            int cs,ce;
            tie(ce,cs)=pq.top();
            pq.pop();
            for(int i = cs; i <=ce; i++){
                if(!v[i]){
                    v[i]=1;
                    ans++;
                    break;
                }
            }
        }
        cout << ans << '\n';
    }
}