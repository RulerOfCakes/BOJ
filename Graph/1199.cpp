#include <bits/stdc++.h>

using namespace std;
int N;
int arr[1002][1002];
int pos[1002];//current check position in dfs

bool check(){
    for(int i = 1; i <= N; i++){
        int cnt = 0;
        for(int j = 1; j <= N; j++){
            cnt += arr[i][j];
        }
        if(cnt&1)return 0;
        
    }
    return 1;
}

void dfs(int now){
    for(int &i = pos[now]; i <= N; i++){
        while(arr[now][i]){
            arr[now][i]--;
            arr[i][now]--;
            dfs(i);
        }
    }
    cout << now << ' ';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> arr[i][j];
        }
    }
    if(!check()){
        cout << -1;
        return 0;
    }
    for(int i = 1; i <= N; i++)pos[i]=1;
    dfs(1);
}