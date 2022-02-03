#include <bits/stdc++.h>
using namespace std;
int N,M;
int parent[101010];
int find(int x){
    if(parent[x]==x)return x;
    else return parent[x]=find(parent[x]);
}
void uni(int x, int y){
    int px=find(x),py=find(y);
    if(px!=py){
        parent[px]=py;
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M;
    for(int i = 0; i <= N; i++)parent[i]=i;
    for(int i = 0; i < M; i++){
        int a,b;
        cin>>a>>b;
        uni(a,b);
    }
    int px=-1,ans=0;
    for(int i = 0; i < N; i++){
        int a;cin>>a;
        if(px==-1)px=find(a);
        else{
            int pt=find(a);
            if(px!=pt)ans++;
            px=pt;
        }
    }
    cout << ans;
}