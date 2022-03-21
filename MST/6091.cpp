#include <bits/stdc++.h>
using namespace std;
using ti = tuple<int,int,int>;
int N;
int adj[1025][1025];
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    for(int i = 1; i <= N; i++){
        for(int j = i+1; j <= N; j++){
            cin>>adj[i][j];
            adj[j][i]=adj[i][j];
        }
    }
    vector<vector<int>> conv(1025,vector<int>());
    priority_queue<ti,vector<ti>,greater<ti>> pq;
    pq.push(make_tuple(0,1,0));
    while(!pq.empty()){
        auto [cc,cx,px]=pq.top();
        pq.pop();
        if(conv[cx].size())continue;
        conv[px].push_back(cx);
        conv[cx].push_back(px);
        for(int i = 1; i <= N; i++){
            if(conv[i].size()||i==cx)continue;
            pq.push(make_tuple(adj[cx][i],i,cx));
        }
    }
    for(int i = 1; i <= N; i++){
        cout << (i==1?conv[i].size()-1:conv[i].size()) << ' ';
        sort(conv[i].begin(),conv[i].end());
        for(int x : conv[i]){
            if(x==0)continue;
            cout << x << ' ';
        }
        cout << '\n';
    }
}