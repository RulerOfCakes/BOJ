#include <bits/stdc++.h>
using namespace std;
int T,N,K;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    cin >> T;
    while(T--){
        cin >> N >> K;
        vector<int> time(N+1);
        vector<int> ctime(N+1,0);
        vector<vector<int>>edges(N+1,vector<int>());
        vector<int> indeg(N+1);
        for(int i = 0; i < N; i++){
            cin >> time[i+1];
        }
        for(int i = 0; i < K; i++){
            int a,b;
            cin >> a >> b;
            edges[a].push_back(b);
            indeg[b]++;
        }
        queue<int> q;
        for(int i = 1; i <= N; i++){
            if(!indeg[i]){
                q.push(i);
                ctime[i]=time[i];
            }
        }
        int W;
        cin >> W;
        while(!q.empty()){
            int cx = q.front();
            q.pop();
            for(auto nx : edges[cx]){
                if(!--indeg[nx]){
                    q.push(nx);
                }
                if(ctime[nx]<ctime[cx]+time[nx]){
                    ctime[nx]=ctime[cx]+time[nx];
                }
            }
        }
        cout << ctime[W] << '\n';
    }
}