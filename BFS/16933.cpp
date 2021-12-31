#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;
using ppi = pair<pi,pi>;
int N,M,K;
int arr[1002][1002];
int visited[1002][1002][11][2];
int dx[]={0,0,-1,1},dy[]={1,-1,0,0};

int bfs(){
    queue<ppi> pq;
    pq.push({{1,0},{0,0}});
    int ret=-1;
    visited[0][0][0][1]=1;
    while(!pq.empty()){
        auto [p1,p2] = pq.front();
        auto [cx,cy] = p2; auto [cc,cw]=p1;
        bool cp = cc%2;
        //cout << cx << cy << cc << endl;
        pq.pop();
        if(cx==N-1&&cy==M-1){
            if(ret==-1)ret=cc;
            else ret=min(ret,cc);
        }
        if(visited[cx][cy][cw][cp]<cc)continue;
        bool wt=0;
        for(int i = 0 ; i < 4; i++){
            int nx=dx[i]+cx,ny=dy[i]+cy;
            if(nx<0||nx>=N||ny<0||ny>=M)continue;
            if(arr[nx][ny]){
                wt=1;
                if(!cp||cw>=K||visited[nx][ny][cw+1][!cp]<=cc+1)continue;
                visited[nx][ny][cw+1][!cp]=cc+1;
                pq.push({{cc+1,cw+1},{nx,ny}});
            }
            else{
                if(visited[nx][ny][cw][!cp]<=cc+1)continue;
                visited[nx][ny][cw][!cp]=cc+1;
                pq.push({{cc+1,cw},{nx,ny}});
            }
        }
        if(visited[cx][cy][cw][!cp]>cc+1){
            visited[cx][cy][cw][!cp]=cc+1;
            pq.push({{cc+1,cw},{cx,cy}});
        }
    }
    return ret;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N>>M>>K;
    for(int i = 0; i <= N; i++)for(int j = 0; j <= M; j++)for(int k = 0; k <= K; k++)for(int l = 0; l < 2; l++)visited[i][j][k][l]=1e9;
    //memset(visited,0xc0,sizeof(visited));
    for(int i = 0; i < N; i++){
        string s;
        cin>>s;
        for(int j = 0; j < M; j++){
            arr[i][j]=s[j]-'0';
        }
    }
    cout << bfs();
}