#include <bits/stdc++.h>
using namespace std;
int N,M;
vector<int> adj[201010];
int taken[201010],Acnt,Bcnt;

vector<int> pth,B;
void dfs(int cx, int prt){
    if(Acnt==Bcnt)return;
    taken[cx]=2;Acnt--;
    pth.push_back(cx);

    for(int nx : adj[cx]){
        if(taken[nx]||Acnt==Bcnt)continue;
        dfs(nx,cx);
    }

    if(Acnt==Bcnt)return;
    taken[cx]=1;Bcnt++;
    B.push_back(cx);
    pth.pop_back();
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> M;
    Acnt=N;
    for(int i = 0 ; i < M; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,0);
    cout << pth.size() << ' ' << Acnt << '\n';
    for(auto x : pth){
        cout << x << ' ';
    }
    cout << '\n';
    if(!Acnt)return 0;
    for(int i = 1; i <= N; i++){
        if(!taken[i])cout << i << ' ';
    }
    cout << '\n';
    for(auto x : B)cout << x << ' ';
}