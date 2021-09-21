#include <bits/stdc++.h>

using namespace std;

int N, M;
const int INF = 1e9;
int dp[102][102];
int psum[102];
bool check[102][102];
vector<int>v;

//max from making cnt ranges using 1 to cx
int sol(int cx, int cnt){
    if(!cnt)return 0;
    if(cx<=0)return -INF;

    if(check[cx][cnt])return dp[cx][cnt];
    check[cx][cnt]=1;

    int& ret = dp[cx][cnt];

    ret = sol(cx-1,cnt); //result of skipping this block
    for(int i = 1;i  <= cx; i++){
        ret=max(ret,sol(i-2,cnt-1)+psum[cx]-psum[i-1]);
    }
    return ret;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    v=vector<int>(N+1,0);
    int ans = 0;
    for(int i = 1; i <= N; i++){
        cin >> v[i];
        psum[i]=psum[i-1]+v[i];
    }

    cout << sol(N,M);

}