#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<char,ll>;

int N;
ll ans;
pi stat[123458];
vector<int> adj[123458];

void dfs(int sx, ll& wolves, int prt){
    char c;ll nums;
    tie(c,nums)=stat[sx];
    if(c=='W')wolves+=nums;
    else{
        ans+=max(0LL,nums-wolves);
        wolves-=min(nums, wolves);
    }
    ll prev = wolves-nums;
    for(auto nx : adj[sx]){
        if(nx==prt)continue;
        dfs(nx,wolves,sx);
    }
    if(c=='W'){
        wolves=min(wolves,prev);
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(0);
    cin>>N;
    for(int i =2; i <= N; i++){
        int a,b;
        char c;
        cin>>c>>a>>b;
        stat[i]={c,a};
        adj[i].push_back(b);
        adj[b].push_back(i);
    }
    ll w = 0;
    dfs(1,w,0);
    cout << ans;
}