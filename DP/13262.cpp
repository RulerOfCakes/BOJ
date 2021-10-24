#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, D;
ll v[5010], dp[5008][5080];
int idx[5008][5080];
ll cost[5008][5080];
void DnCo(int t, int s,int e,int is,int ie)
{
    if(s>e)return;
    int mid=(s+e)/2;
    int& id = idx[t][mid];
    id=-1;
    dp[t][mid]=-1;
    
    for(int i=is;i<=min(ie,mid);i++)
    {
        ll tmp = dp[t-1][i-1]+cost[i][mid];
        if(dp[t][mid]<tmp){
            dp[t][mid]=tmp;
            id=i;
        }
    }
    
    DnCo(t,s,mid-1,is,id);
    DnCo(t,mid+1,e,id,ie);
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> D;
    
    for(int i = 1; i <= N; i++){
        cin >> v[i];
    }
    for(int i = 1; i <= N; i++){
        cost[i][i]=v[i];
        for(int j = i+1; j <= N;j ++){
            cost[i][j]=cost[i][j-1]|v[j];
        }
    }
    for(int i = 0; i <= N; i++){
        dp[1][i]=cost[1][i];
        idx[1][i]=1;
    }
    for(int t = 2; t <= D; t++)DnCo(t,t,N,t,N);
    cout << dp[D][N];
}