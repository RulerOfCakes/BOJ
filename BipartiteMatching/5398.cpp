#include <bits/stdc++.h>

using namespace std;

using Edge = tuple<int, int, int>;
using pi = pair<int, int>;

int T,H,V;
const int INF = 1e9;
vector<bool> visited;
vector<int> match2;
vector<vector<int>> v;
char varr[2002][2002],harr[2002][2002];
int vnarr[2002][2002],hnarr[2002][2002];
bool dfs(int x){
    if(visited[x])return false;
    visited[x]=1;

    for(int i : v[x]){
        if(!match2[i] || dfs(match2[i])){
            //match1[x]=i;
            match2[i]=x;
            return true;
        }
    }
    return false; 
}

int main(){
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>T;
    while(T--){
        cin >> H >> V;
        v = vector<vector<int>>(H+2, vector<int>());
        //match1 = vector<int>(N+1, 0);
        match2 = vector<int>(V+2, 0);
        memset(vnarr,0,sizeof(vnarr));
        memset(hnarr,0,sizeof(hnarr));
        for(int i = 0; i  < H; i++){
            int a,b; string s;
            cin>>a>>b>>s;
            for(int x = a; x < a+s.length(); x++){
                harr[x][b] = s[x-a];
                hnarr[x][b]=i+1;
            }
        }
        for(int i = 0; i  < V; i++){
            int a,b; string s;
            cin>>a>>b>>s;
            for(int y = b; y < b+s.length(); y++){
                varr[a][y] = s[y-b];
                vnarr[a][y]=i+1;
                //cout << a << ' ' << y << ' ' << hnarr[a][y] << '\n';
                if(hnarr[a][y]!=0&&harr[a][y]!=varr[a][y]){
                    //cout << "WOWZERS\n";
                    v[hnarr[a][y]].push_back(vnarr[a][y]);
                }
            }
        }
        
        int ans=0;

        for(int i = 1; i <= H; i++){
            visited = vector<bool>(H+2, 0);

            if(dfs(i))ans++;
        }
        cout << H+V-ans << '\n';
    }
}