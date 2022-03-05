#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
using ll = long long;
int N,C;
vector<pi> X[505050],Y[505050];
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N >> C;

    for(int i = 0 ; i < N; i++){
        int x,y,v;
        cin>>x>>y>>v;
        X[x].push_back({y,v});
        Y[y].push_back({x,v});
    }
    ll ans = 0,tans=0;
    int y = 0, x = 1e5,cost=0;
    while(y<=100001&&x){
        if(cost<=C){
            ans=max(ans,tans);
            for(auto p : Y[y++]){
                if(p.first<=x){
                    ++cost;
                    tans+=p.second;
                }
            }
        } else {
            for(auto p : X[x--]){
                if(p.first<y){
                    --cost;
                    tans-=p.second;
                }
            }
        }
        if(cost<=C)ans=max(ans,tans);
    }
    ans=max(ans,tans);
    cout << ans;
}