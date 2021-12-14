#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = tuple<int, int, int>;

int N, M;
priority_queue<Edge> ev;
int parent[1002];

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
        int a, b, c;
        cin >> a >> b >> c;
        ev.push({-c, a, b});
    }
    int ans = 0;
    while(!ev.empty()){
        int weight, x, y;
        tie(weight, x, y) = ev.top();
        weight = -weight;
        ev.pop();
        if(find(x)!=find(y)){
            uni(x,y);
            ans+=weight;
        }
    }    
    cout << ans;
} 