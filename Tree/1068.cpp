#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;
int N, M;
vector<int> parent;
vector<vector<int>> child;
int root;
int dfs(){
    stack<int> s;
    s.push(root);
    vector<int> visited(N);
    int ret=0;
    visited[root]=1;
    while(!s.empty()){
        int cx = s.top();
        s.pop();
        if(child[cx].empty())ret++;
        for(auto nxt : child[cx]){
            if(visited[nxt])continue;

            visited[nxt]=1;
            s.push(nxt);
        }
    }
    return ret;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    parent=vector<int>(N);
    child=vector<vector<int>>(N,vector<int>());
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        parent[i]=a;
        if(a!=-1){
            child[a].push_back(i);
        }
        else root = i;
    }
    int x;
    cin >> x;
    int tx = parent[x];
    if(tx==-1){
        cout << 0;
        return 0;
    }
    else
        for(auto iter = child[tx].begin(); iter != child[tx].end(); iter++){
            if(*iter==x){
                child[tx].erase(iter);
                break;
            }
        }
    cout << dfs();
}