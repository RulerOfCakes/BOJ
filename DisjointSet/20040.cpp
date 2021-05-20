#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M;

int parent[500002];

int find(int node)
{
    if (node == parent[node])
    {
        return node;
    }
    return parent[node] = find(parent[node]);
}

bool uni(int a, int b)
{
    int ar = find(a), br = find(b);
    if(br==ar){
        return true;
    }
    parent[br] = ar;
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i <= N; i++)
    {
        parent[i] = i;
    }
    int ans = 0;
    for(int i = 0 ; i < M; i++){
        int a, b;
        cin >> a >> b;
        assert(a!=b);
        bool check = uni(min(a,b), max(a,b));
        if(check){
            if(!ans)
            ans = i+1;
        }
    }
    cout << ans;
}