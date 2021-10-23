#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, D;
ll v[8010], sum[8080], dp[808][8080];
int idx[808][8080];
ll cost(int i, int j){return (sum[j]-sum[i-1])*(j-i+1);}
void DnCo(int t, int s,int e,int is,int ie)
{
    if(s>e)return;
    int mid=(s+e)/2;
    int& id = idx[t][mid];
    id=-1;
    dp[t][mid]=-1;
    
    for(int i=is;i<=ie;i++)
    {
        ll tmp = dp[t-1][i]+cost(i+1,mid);
        if(dp[t][mid]==-1||dp[t][mid]>tmp){
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
        sum[i]=sum[i-1]+v[i];
    }
    for(int i = 0; i <= N; i++){
        dp[1][i]=cost(1,i);
        idx[1][i]=0;
    }
    for(int t = 2; t <= D; t++)DnCo(t,0,N,0,N);
    cout << dp[D][N];
}