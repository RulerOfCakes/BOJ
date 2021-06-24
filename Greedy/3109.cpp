#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int R, C;
char tmap[10002][502];
int ans;

bool dfs(int sx, int sy)
{
    if(sy==C-1){
        ans++;
        return true;
    }
    for(int i = sx-1; i <= sx+1; i++){
        if(i<0||i>=R)continue;
        if(tmap[i][sy+1]=='x')continue;
        tmap[i][sy+1]='x';
        if(dfs(i, sy+1))return true;
    }
    return false;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> R >> C;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> tmap[i][j];
        }
    }
    //cout << endl;
    for(int i = 0; i < R; i++){
        if(tmap[i][0]!='x'){
            dfs(i, 0);
        }
    }
    cout << ans;
}