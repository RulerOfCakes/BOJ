#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int N,ans;
vector<pi> adj[10002];

int dfs(int x){
    int a1=0,a2=0;
    //choose only one from each branch
    for(auto [nx,nc] : adj[x]){
        int sum = dfs(nx) + nc;
        if(sum>a1){
            a2=a1;
            a1=sum;
        }
        else if(sum>a2){
            a2=sum;
        }
    }
    if(ans<a1+a2)ans=a1+a2;
    return a1;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    for(int i = 0; i < N-1; i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
    }
    dfs(1);
    cout << ans;
}