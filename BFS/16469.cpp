#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int N,M;
int ans,cnt;
pi evil[3];
int arr[102][102];
int dist[102][102][3];
int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
int full(int x, int y){
    if((dist[x][y][0]!=-1)&&(dist[x][y][1]!=-1)&&(dist[x][y][2]!=-1)){
        return max({dist[x][y][0],dist[x][y][1],dist[x][y][2]});
    }
    else return 0;
}
void bfs(){
    queue<pair<int,pi>> q;
    for(int i = 0; i < 3; i++){
        q.push({i,{evil[i].first-1,evil[i].second-1}});
        dist[evil[i].first-1][evil[i].second-1][i]=0;
    }
    while(!q.empty()){
        int cc=q.front().first,cx,cy;
        tie(cx,cy)=q.front().second;
        q.pop();
        //cout << cx << ' ' << cy << ' ' << cc << endl;
        
        for(int i = 0; i < 4; i++){
            int nx=cx+dx[i],ny=cy+dy[i];
            if(nx<0||nx>=N||ny<0||ny>=M)continue;
            if(arr[nx][ny]==1||dist[nx][ny][cc]!=-1)continue;
            dist[nx][ny][cc]=dist[cx][cy][cc]+1;
            q.push({cc,{nx,ny}});
            if(int tmp = full(nx,ny)){
                if(ans>tmp){
                    ans=tmp;
                    cnt=1;
                }
                else if(ans==tmp){
                    cnt++;
                }
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            for(int k = 0 ; k < 3; k++){
                dist[i][j][k]=-1;
            }
        }
    }
    for(int i = 0; i < N; i++){
        string s;
        cin>> s;
        for(int j = 0; j < M; j++){
            arr[i][j]=s[j]-'0';
        }
    }
    for(int i = 0; i < 3; i++){
        cin >> evil[i].first >> evil[i].second;
    }
    ans=1e9;
    cnt=1;
    bfs();
    if(ans==1e9){
        cout <<-1;
    }
    else
        cout << ans << '\n' << cnt;
}