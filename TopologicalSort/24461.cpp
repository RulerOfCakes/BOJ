#include <bits/stdc++.h>

using namespace std;

int N;
int indeg[100003];
bool visited[100003];
vector<int> edges[100003];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    int cnt=0;
    for(int i = 1; i < N; i++){
        int a,b;
        cin>>a>>b;
        edges[a].push_back(b);
        edges[b].push_back(a);
        indeg[a]++;indeg[b]++;
        if(indeg[a]==3)cnt++;
        if(indeg[b]==3)cnt++;
    }
    queue<int> q;
    for(int i = 0; i < N; i++){
        if(indeg[i]==1){
            q.push(i);
        }
    }
    int ncnt=0;
    while(!q.empty()&&ncnt<cnt){
        queue<int> nq;
        while(!q.empty()){
            int curp = q.front();
            q.pop();
            visited[curp]=1;

            for(auto next : edges[curp]){
                if(--indeg[next]==1){
                    nq.push(next);
                }
                if(indeg[next]==2){
                    ncnt++;
                }
            }
        }
        q=nq;
    }

   
    for(int i = 0; i < N; i++){
        if(!visited[i])cout<<i<<' ';
    }
}