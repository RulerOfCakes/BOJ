#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;
using ll = long long;
int N,L,R;
deque<pi> adj[202020];
vector<int> ans;
void dfs(int cx,int i){
    if(ans.size()>R)return;
    ans.push_back(cx);
    for(auto [nx,ni] : adj[cx]){
        if(ni<i)break;
        if(ans.size()>R)return;
        dfs(nx,ni);
    }
}
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(0);
    cin>>N>>L>>R;
    for(int i= 0 ;i  < N; i++){
        int x,y;
        cin >> x >> y;
        adj[x].push_front({y,i});
    }
    dfs(0,0);
    int l = L%ans.size(), range = R-L;
    for(int i = l, cnt=0; cnt<range; i=(i+1)%ans.size(),cnt++){
        cout << ans[i] << ' ';
    }
}