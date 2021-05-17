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
    if(ar!=br)
    cnt[ar] += cnt[br];
    parent[br] = ar;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    for(int i = 1; i <= 1000000; i++){
        parent[i]=i;
        cnt[i]=1;
    }
    for(int i = 0; i < N; i++){
        char cmd;
        cin >> cmd;
        if(cmd=='I'){
            int a, b;
            cin >> a >> b;
            uni(a,b);
        }else{
            int c;
            cin>>c;
            cout << cnt[find(c)]<<'\n';
        }
    }
}