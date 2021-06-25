#include <bits/stdc++.h>

using namespace std;
int G,P;
int parent[100002];

int find(int node)
{
    if (node == parent[node])
    {
        return node;
    }
    return parent[node] = find(parent[node]);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> G >> P;
    int ans = 0;
    bool over=0;
    for(int i = 0; i <= G; i++){
        parent[i]=i;
    }
    for(int i = 0; i < P; i++){
        int a;
        cin >> a;
        if(over)continue;
        int tmp = find(a);
        if(tmp==0){
            over=1;
        }
        else{
            ans++;
            parent[tmp]=tmp-1;
        }
    }
    cout << ans;
}