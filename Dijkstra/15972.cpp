#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;
using ll = long long;
using Edge = tuple<int,int,int,int,int>;

int N, M, H;

vector<vector<pi>> v;
vector<vector<int>> flights;

int djikstra(){
    vector<vector<ll>> vst(N+1, vector<ll>(2, 1e11));
    priority_queue<pair<pi, int>> pq;
    // vst[S]=1;
    ll ans = 1e11;
    pq.push({{0, S}, 0});
    while(!pq.empty()){
        ll cl, cc; int fly;
        cl=pq.top().first.second;
        cc=-pq.top().first.first;
        fly = pq.top().second;
        pq.pop();
        if(vst[cl][fly]<=cc)continue;
        
        vst[cl][fly]=cc;
        if(cl==T){
            ans=min(ans,cc);
            //cout << "honeydetected" << ans << '\n';
            continue;
        }
        if(fly==0){
            for(auto i : flights[cl]){
                if(vst[i][1]<=cc)continue;
                pq.push({{-cc, i}, 1});
            }
        }
        for(auto i : v[cl]){
            if(vst[i.first][fly]<=cc+i.second)continue;
            pq.push({{-(cc+i.second), i.first}, fly});
        }
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> H;
    v = vector<vector<pi>>((N+2)*(M+2)+1, vector<pi>());
    flights = vector<vector<int>>(N+1, vector<int>());
    for(int i = 0; i <= N; i++){
        for(int j  =0; j < M; j++){
            int a;
            cin >> a;
        }
    }
}