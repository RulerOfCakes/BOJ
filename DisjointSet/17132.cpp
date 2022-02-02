#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N;
int parent[100002]; 
ll sz[100002];
int find(int x){
    if(parent[x]==x)return x;
    else return parent[x]=find(parent[x]);
}

void uni(int x, int y){
    int px=find(x),py=find(y);
    if(px!=py){
        parent[px]=py;
        sz[py]+=sz[px];
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    for(int i = 0; i <= N; i++)parent[i]=i,sz[i]=1;
    vector<tuple<int,int,int>> edges;
    for(int i = 0; i < N-1; i++){
        int a,b,c;
        cin>>a>>b>>c;
        edges.push_back(make_tuple(c,a,b));
    }
    ll ans=0;
    sort(edges.begin(),edges.end(),greater<tuple<int,int,int>>());
    for(auto [w,from,to]:edges){
        int pf=find(from),pt=find(to);
        if(pf==pt)continue;
        ans+=sz[pf]*sz[pt]*w;
        uni(from,to);
    }
    cout << ans;
}