#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M;

int parent[202];

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
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int a;
            cin >> a;
            if(a){
                uni(j+1, i+1);
            }
        }
    }
    int a;
    cin >> a;
    int pr=find(a);
    for(int i = 1; i< M; i++){
        
        cin >> a;
        if(pr!=find(a)){
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
}