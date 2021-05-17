#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M;
const int INF = 1e6;

int parent[1000002];
int cnt[1000002];

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
    for(int i = ar; i <= br; i = find(i+1)){
        parent[i]=br;
        cnt[br]+=cnt[i];
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;

    for(int i = 1; i <= N+1; i++){
        parent[i]=i;
        cnt[i]=1;
    }
    for(int i = 0; i < M; i++){
        int a, b;
        cin >> a >> b;
        uni(a,b);
    }
    int ans = 0;
    for(int i = find(1); i <= N; i=find(i+1)){
        ans++;
    }
    cout << ans;
}