#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
int T, N, M;
char arr[102][102];
int visited[102][102]; //values are bitmasked key values
vector<vector<pi>> locks;
bool validlocks[27];
int ans = 0;
int keys = 0;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
//many keys, many doors
void bfs(int sx, int sy){
    queue<pi> q;
    q.push({sx, sy});
    visited[sx][sy]=1;

    while(!q.empty()){
        int cx, cy;
        tie(cx, cy) = q.front();
        q.pop();
        //cout << "going through " << cx << ' ' << cy << '\n';
        for(int i = 0; i < 4; i++){
            int nx = cx+dx[i], ny = dy[i]+cy;
            if(nx<1||ny<1||nx>N||ny>M)continue;
            if(visited[nx][ny])continue;
            if(arr[nx][ny]=='*')continue;
            if(arr[nx][ny]>='A'&&arr[nx][ny]<='Z')
                if(!(keys&(1<<(arr[nx][ny]-'A')))){
                    locks[arr[nx][ny]-'A'].push_back({nx, ny});
                    
                    continue;
                }
                
            
            visited[nx][ny]=1;
            q.push({nx, ny});
            if(arr[nx][ny]=='$'){
                ans++;
                continue;
            }
            if(arr[nx][ny]>='a' && arr[nx][ny]<= 'z'){
                if(!(keys&(1<<(arr[nx][ny]-'a')))){
                    keys += 1<<(arr[nx][ny]-'a');
                    validlocks[arr[nx][ny]-'a']=1;
                    //maybe initiate search on locks
                    for(pi k : locks[arr[nx][ny]-'a']){
                        bfs(k.first, k.second);
                    }
                }
            }
        }
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>T;
    while(T--){
        ans = 0; keys = 0;
        locks = vector<vector<pi>>(27, vector<pi>());
        fill(validlocks, validlocks+27, 0);
        cin >> N >> M;
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= M; j++){
                cin >> arr[i][j];
                visited[i][j]=0;
            }
        }
        string s;
        cin >> s;
        for(int i = 0; i < s.size(); i++){
            if(s[i]=='0')break;
            if(keys&(1<<(s[i]-'a')))continue;
            keys += (1<<(s[i]-'a'));
            validlocks[s[i]-'a']=1;
        }
        for(int i = 1; i <= N; i++){
            if(i==1||i==N){
                for(int j = 1; j <= M; j++){
                    if(arr[i][j]!='*'){
                        if(visited[i][j])continue;
                        if(arr[i][j]=='.'){
                            bfs(i, j);
                        } else if (arr[i][j] <= 'Z' && arr[i][j] >= 'A') {
                            if(keys&(1<<(arr[i][j]-'A'))){
                                bfs(i, j);
                            } else {
                                locks[arr[i][j]-'A'].push_back({i, j});
                            }
                        } else if(arr[i][j] <= 'z' && arr[i][j] >= 'a'){
                            if(!(keys&(1<<(arr[i][j]-'a')))){
                                keys+=1<<(arr[i][j]-'a');
                                validlocks[arr[i][j]-'a']=1;
                                bfs(i, j);
                                for(pi k : locks[arr[i][j]-'a']){
                                    bfs(k.first, k.second);
                                }
                            }
                            else bfs(i,j);
                            
                        } else {
                            ans++;
                            bfs(i, j);
                        }
                    }
                }
            } else {
                for(int j : {1, M}){
                    if(arr[i][j]!='*'){
                        if(visited[i][j])continue;
                        if(arr[i][j]=='.'){
                            bfs(i, j);
                        } else if (arr[i][j] <= 'Z' && arr[i][j] >= 'A') {
                            if(keys&(1<<(arr[i][j]-'A'))){
                                bfs(i, j);
                            } else {
                                locks[arr[i][j]-'A'].push_back({i, j});
                            }
                        } else if(arr[i][j] <= 'z' && arr[i][j] >= 'a'){
                            if(!(keys&(1<<(arr[i][j]-'a')))){
                                keys+=1<<(arr[i][j]-'a');
                                validlocks[arr[i][j]-'a']=1;
                                bfs(i, j);
                                for(pi k : locks[arr[i][j]-'a']){
                                    bfs(k.first, k.second);
                                }
                            }
                            else bfs(i,j);
                            
                        } else {
                            ans++;
                            bfs(i, j);
                        }
                    }
                }
            }
        }
        
        
        cout << ans << '\n';
    }
}