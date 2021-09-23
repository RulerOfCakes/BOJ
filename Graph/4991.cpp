#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int,int>;
int N, M;
const int INF = 1e9;
char arr[22][22];
int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};
vector<pi> dirty;
map<pair<int,int>,int> mp;//stores dirt idx info
vector<vector<vector<int>>> visited;
int fin;
int bfs(int sx, int sy){

    queue<pair<int,pi>> q;
    q.push({0,{sx,sy}});//state,coords
    visited[sx][sy][0]=0;
    int ret = INF;
    while(!q.empty()){
        int cs=q.front().first,cx=q.front().second.first,cy=q.front().second.second;
        int cval = visited[cx][cy][cs];
        //cout << cs << ' ' << cx << ' ' << cy << ' ' << cval << endl;
        //cout << endl;
        q.pop();
        if(cs==fin){
            //cout << fin << ' ' << ret << ' ' << cval << endl;
            ret=min(ret,cval);
            continue;
        }
        for(int i  =0 ;i < 4; i++){
            int nx = cx+dx[i], ny = cy + dy[i];
            if(nx<0||nx>=N||ny<0||ny>=M)continue;
            if(arr[nx][ny]=='x')continue;
            if(visited[nx][ny][cs]!=-1&&visited[nx][ny][cs]<=cval+1)continue;
            
            visited[nx][ny][cs]=visited[cx][cy][cs]+1;
            if(arr[nx][ny]=='*'){
                int nidx = mp[{nx,ny}];
                if((cs&(1<<nidx))){
                    q.push({cs,{nx,ny}});
                    continue;
                }
                int ns = cs|(1<<nidx);
                q.push({ns,{nx,ny}});
                visited[nx][ny][ns]=visited[cx][cy][cs]+1;
            }
            else{
                q.push({cs,{nx,ny}});
            }
        }
        
    }
    if(ret==INF){
        return -1;
    }
    else return ret;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while(true){
        cin >> M >> N;
        if(!N&&!M)break;
        dirty=vector<pi>();
        mp=map<pi,int>();
        int sx,sy;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                cin >> arr[i][j];
                if(arr[i][j]=='*'){
                    dirty.push_back({i,j});
                    mp[{i,j}] = dirty.size()-1;
                }
                if(arr[i][j]=='o'){
                    sx=i;
                    sy=j;
                }
            }
        }
        fin = (1<<dirty.size())-1;
        
        visited=vector<vector<vector<int>>>(N,vector<vector<int>>(M,vector<int>(1<<12,-1)));
        
        cout << bfs(sx,sy) << '\n';
    }
}