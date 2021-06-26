#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
using ll = long long;
int N;
vector<int> parent;

int find(int a){
    if(parent[a]==a){
        return a;
    }
    return parent[a] = find(parent[a]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    priority_queue<pi> pq;
    vector<bool> filled(N+1, 0);
    parent = vector<int>(N+1, 0);
    for(int i = 0; i <= N; i++){
        parent[i]=i;
    }
    for(int i = 0; i < N; i++){
        int a, b;
        cin >> a >> b;
        pq.push({b, a});
    }
    ll ans = 0;
    while(!pq.empty()){
        int curd, curc;
        tie(curc, curd) = pq.top();
        pq.pop();
        int loc = find(curd);
        if(loc==0){
            continue;
        }
        parent[loc]=loc-1;
        ans += curc;
    }
    cout << ans;
}