#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, K;
const int INF = 1e9;

int dp[202][102];

//combination memoization
int comb(int n, int r){
    if(n==r||r==0)return 1;
    int &ret = dp[n][r];
    if(ret!=-1)return ret;
    int t1=comb(n-1,r-1),t2=comb(n-1,r);
    if(t1+t2>INF)return ret=INF;
    return ret=t1+t2;
}

void sol(int n, int m, int k){
    int tmp=comb(n+m-1,n-1);
    if(n>0&&k<=tmp){
        cout << 'a';
        sol(n-1,m,k);
    } else if(m>0){
        cout << 'z';
        sol(n,m-1,k-tmp);
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> K;
    memset(dp,-1,sizeof(dp));
    if(comb(N+M,N)<K)cout << -1;
    else sol(N,M,K);

}