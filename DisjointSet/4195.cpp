#include <bits/stdc++.h>
using namespace std;
int N,M;
int prt[201010];
int sz[201010];
int find(int x){
    if(x==prt[x])return x;
    else return prt[x]=find(prt[x]);
}
int uni(int x, int y){
    int px=find(x),py=find(y);
    if(px!=py){
        prt[py]=px;
        sz[px]+=sz[py];
    }
    return sz[px];
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    while(N--){
        cin>>M;
        int cnt=0;
        map<string,int> mp;
        vector<pair<int,int>> qv;
        for(int i = 0; i < M; i++){
            string s1,s2;
            cin>>s1>>s2;
            if(!mp[s1]){
                mp[s1]=++cnt;
            }
            if(!mp[s2]){
                mp[s2]=++cnt;
            }
            qv.push_back({mp[s1],mp[s2]});
        }
        for(int i = 1; i <= cnt; i++)prt[i]=i,sz[i]=1;
        for(auto [p1,p2] : qv){
            cout << uni(p1,p2) << '\n';
        }
    }
}