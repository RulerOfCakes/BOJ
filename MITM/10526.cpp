#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N;ll L;
ll adj[15][15];
vector<map<ll,bool>> dp;
map<int,int> possible;

int bb;
void btrk(int cx, int bit, ll cc, int cnt){
    if(cnt>=N/2){
        if(cx==0){
            possible[bit]=1;
            dp[bit][cc]=1;
        }
        if(cnt==N/2+N%2)
            return;
    }
    for(int nx = 0; nx < N; nx++){
        if(nx==bb)continue;
        if(bit&(1<<nx))continue;
        if(cnt+1<N/2&&nx==0)continue;
        btrk(nx,bit|(1<<nx),cc+adj[cx][nx],cnt+1);
    }
}

bool sol(){
    for(int i = 1; i < N; i++){
        bb=i;
        dp=vector<map<ll,bool>>(1<<15);
        possible=map<int,int>();
        btrk(i,0,0,0);
        vector<bool> visited(1<<15);
        for(auto [cx,cc] : possible){
            if(visited[cx])continue;
            int nx = (cx^((1<<N)-1))+1-(1<<i);
            // bitset<8> ba(cx),bb(nx);
            // cout << i << ": " << ba << ' ' << bb << '\n';
            if(possible.count(nx)){
                visited[nx]=1;
                for(auto [nc, nb] : dp[cx]){
                    if(nb&&dp[nx].count(L-nc))return true;
                }
            }
        }
    }

    return false;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>L;

    for(int i =0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin>>adj[i][j];
        }
    }
    cout << (sol()?"possible":"impossible");
}