#include <bits/stdc++.h>
using namespace std;
int N,M,Q;
int parent[101010];
int sz[2][101010];
int find(int x){
    if(parent[x]==x)return x;
    else return parent[x]=find(parent[x]);
}
void uni(int x, int y){
    int px=find(x),py=find(y);
    if(px!=py){
        parent[px]=py;
        sz[0][py]+=sz[0][px];
        sz[1][py]+=sz[1][px];
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M>>Q;
    for(int i = 1; i <= N; i++){
        int x;cin>>x;
        if(x)sz[0][i]=1;else sz[1][i]=1;
        parent[i]=i;
    }
    for(int i = 0; i < M; i++){
        int a,b;
        cin>>a>>b;
        uni(a,b);
    }
    while(Q--){
        int x;cin>>x;
        int px = find(x);
        if(sz[0][px]>sz[1][px])cout << 1 << '\n';
        else cout << 0 << '\n';
    }
}