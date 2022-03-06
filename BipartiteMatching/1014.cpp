#include <bits/stdc++.h>
using namespace std;
int T,N,M;
vector<vector<int>> adj;
int match2[6464];
vector<int> visited;
char arr[101][101];

bool dfs(int x){
    if(visited[x])return false;
    visited[x]=1;

    for(int i:adj[x]){
        if(match2[i]==-1 || dfs(match2[i])){
            match2[i]=x;
            //cout << x << ' ' << i << " MATCH\n";
            return true;
        }
    }
    return false; 
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>T;
    while(T--){
        memset(match2,-1,sizeof(match2));
    
        adj=vector<vector<int>>(6464,vector<int>());
        cin>>N>>M;
        vector<int> cv;
        int tot=0;
        for(int i = 0; i < N; i++){
            string s;
            cin>>s;
            for(int j = 0; j < M; j++){
                arr[i][j] = s[j];
                if(arr[i][j] == '.')tot++;
            }
        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j+=2){
                if(arr[i][j]!='.')continue;
                cv.push_back(i*M+j);
                for(int ny : {j-1,j+1}){
                    if(ny<0||ny>=M)continue;
                    for(int nx = i-1; nx <= i+1; nx++){
                        if(nx<0||nx>=N||arr[nx][ny]!='.')continue;
                        adj[i*M+j].push_back(nx*M+ny);
                    }
                }
            }
        }
        int ans = 0;
        for(int x:cv){
            visited=vector<int>(6464);
            if(dfs(x))ans++;
        }
        cout << tot-ans << '\n';
    }
}