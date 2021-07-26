#include <bits/stdc++.h>

using namespace std;
int V, E;
int arr[3002][3002];
//int pos[1002];//current check position in dfs
int parent[3002];

int find(int node)
{
    if (node == parent[node])
    {
        return node;
    }
    return parent[node] = find(parent[node]);
}

void uni(int a, int b)
{
    int ar = find(a), br = find(b);

    parent[br] = ar;
}
bool check(){
    int odd=0;
    for(int i = 1; i <= V; i++){
        int cnt = 0;
        for(int j = 1; j <= V; j++){
            cnt += arr[i][j];
        }
        if(cnt&1){
            odd++;
        }
        
    }
    if(odd==0||odd==2)return 1;
    else return 0;
    
}

// void dfs(int now){
//     for(int &i = pos[now]; i <= N; i++){
//         while(arr[now][i]){
//             arr[now][i]--;
//             arr[i][now]--;
//             dfs(i);
//         }
//     }
//     cout << now << ' ';
// }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> V >> E;
    for(int i = 0; i <= V; i++){
        parent[i] = i;
    }
    for(int i = 0; i < E; i++){
        int a, b;
        cin >> a >> b;
        uni(a,b);
        arr[a][b]=1;
        arr[b][a]=1;
    }
    if(!check()){
        cout << "NO";
        
    }
    else{
        int cur=0;
        for(int i = 1; i <= V; i++){
            int tmp = find(i);
            if(cur!=0&&tmp!=cur){
                cout << "NO";
                return 0;
            }
            cur=tmp;
        }
        cout << "YES";
    }
    // for(int i = 1; i <= N; i++)pos[i]=1;
    // dfs(1);
}