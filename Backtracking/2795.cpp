#include <bits/stdc++.h>

using namespace std;

using ll = long long;
int N, M;
int ans;
bool visit1[102],visit2[102];
vector<int> adj[102];

//dfs from end to start
void toNY(int cx, int cnt){
    if(cnt>=ans)return;
    if(cx==1){
        //destination
        ans=cnt;
        return;
    }
    for(auto nxt : adj[cx]){
        if(visit2[nxt])continue;
        visit2[nxt]=1;
        //checking if we've visited here from first dfs
        toNY(nxt,cnt+!visit1[nxt]);
        visit2[nxt]=0;
    }
}
//dfs from start to end
void toLA(int cx, int cnt){
    if(cnt>=ans)return;
    if(cx==2){
        toNY(2,cnt);
        return;
    }
    for(auto nxt : adj[cx]){
        if(visit1[nxt])continue;
        visit1[nxt]=1;
        toLA(nxt,cnt+1);
        visit1[nxt]=0;
    }
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    ans=N;
    for(int i = 0; i < M; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
    visit1[1]=visit2[2]=1;
    toLA(1,1);
    cout << ans;
}