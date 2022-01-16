#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;

int dp[502][502];
vector<pi> v(502);

int sol(int x, int y){
    if(x==y)return 0;
    if(y-1==x)return v[x].first*v[x].second*v[y].second;
    if(dp[x][y]!=-1)return dp[x][y];
    int& ret=dp[x][y];
    ret=INT_MAX;
    for(int i = x; i < y; i++){
        ret=min(ret,sol(x,i)+sol(i+1,y)+v[x].first*v[i].second*v[y].second);
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin>>N;
    memset(dp,-1,sizeof(dp));
    for(int i = 0; i < N; i++){
        int r,c;
        cin>>r>>c;
        v[i]={r,c};
    }
    cout << sol(0,N-1);
}