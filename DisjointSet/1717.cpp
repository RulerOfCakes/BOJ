#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M;

int parent[1000002];

int find(int node){
    if(node==parent[node]){
        return node;
    }
    return parent[node]=find(parent[node]);
}

void uni(int a, int b){
    int ar=find(a), br=find(b);

    parent[br]=ar;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;
    for(int i = 0; i <= N; i++){
        parent[i]=i;
    }
    for(int i = 0; i < M; i++){
        int c, a, b;
        cin >> c >> a >> b;
        if(c==0){
            uni(a,b);
        }
        else if (c==1)
        {
            int ar = find(a), br = find(b);
            if(ar==br){
                cout << "YES\n";
            }
            else cout << "NO\n";
        }
        
    }
} 