#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;

int T, N;

vector<pi> ec;
bool dp[2][101202];

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> T;
    for(int t = 1; t <= T; t++){
        cin >> N;
        memset(dp,0,sizeof(dp));
        ec=vector<pi>(N+1);
        for(int i = 1; i <= N; i++){
            int a,b;
            cin >> a >> b;
            ec[i]={a,b};
        }
        
        
        sort(ec.begin()+1,ec.end(),[&](pi p1, pi p2){
            return p1.first+p1.second<p2.first+p2.second;
        });
        int ans = 0;
        int lim = ec[N].first+ec[N].second;
        dp[0][0]=1;
        for(int i = 1; i <= N; i++){
            for(int j = 0; j <= lim; j++){
                dp[i%2][j]=dp[(i-1)%2][j];
                if(j-ec[i].second>ec[i].first)break;
                if(j-ec[i].second<0)continue;
                if(dp[(i-1)%2][j-ec[i].second])dp[i%2][j]=1;
            }
        }
        for(int i = 0; i <= lim; i++){
            if(dp[N%2][i])ans=i;
        }
        cout << "Case #" << t << ": " << ans << '\n';
    }
}