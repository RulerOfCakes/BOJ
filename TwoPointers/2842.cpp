#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;
int N,K;
char arr[52][52];
int harr[52][52];
int dx[]={0,0,1,1,1,-1,-1,-1};
int dy[]={1,-1,0,1,-1,0,1,-1};

bool bfs(int sx,int sy, int minl, int maxl){
    int k = 0;
    queue<pi> q;
    vector<vector<bool>> visited(52,vector<bool>(52));
    if(harr[sx][sy]<minl||harr[sx][sy]>maxl)return false;
    visited[sx][sy]=1;
    q.push({sx,sy});
    while(!q.empty()){
        int cx,cy;
        tie(cx,cy)=q.front();
        q.pop();
        for(int i = 0; i < 8; i++){
            int nx=cx+dx[i],ny=cy+dy[i];
            if(nx<0||ny<0||nx>=N||ny>=N)continue;
            if(visited[nx][ny])continue;
            if(harr[nx][ny]<minl||harr[nx][ny]>maxl)continue;
            if(arr[nx][ny]=='K')k++;
            q.push({nx,ny});
            visited[nx][ny]=1;
        }
    }
    assert(k<=K);
    return (k==K?true:false);
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    vector<int> heights;
    int sx,sy;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> arr[i][j];
            if(arr[i][j]=='K')K++;
            else if(arr[i][j]=='P'){
                sx=i,sy=j;
            }
        }
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cin >> harr[i][j];
            heights.push_back(harr[i][j]);
        }
    sort(heights.begin(),heights.end());
    heights.erase(unique(heights.begin(),heights.end()),heights.end());
    int l = 0,r=0,ans=heights.back()-heights.front();
    while(r<heights.size()){
        while(l<heights.size()&&l<=r){
            if(bfs(sx,sy,heights[l],heights[r])){
                ans=min(ans,heights[r]-heights[l]);
                l++;
            }
            else break;
        }
        r++;
    }
    cout << ans;
}