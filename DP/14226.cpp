#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
int N;
const int INF = 1e7;
int dp[2002];
bool visit[2002][2002];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c;
    cin >> N;
    
    visit[1][0] = 1;
    dp[1] = 0;
    queue<pair<int, pi>> q;
    q.push({1, {0, 0}});
    while (!q.empty()){
        int curc = q.front().first,
            curcopy = q.front().second.first,
            curtime = q.front().second.second;
        q.pop();
        if(curc == N){
            break;
        }

        for(int nextc : {curc-1, curc+curcopy, -69}){
            if(nextc == -69){
                if(visit[curc][curc])continue;
                curcopy = curc;
                visit[curc][curcopy] = 1;
                q.push({curc, {curcopy, curtime+1}});
                continue;
            }
            
            if(nextc <= 0 || nextc > 2*N)continue;
            if(curtime+1>1000)continue;
            if(visit[nextc][curcopy] = 1)continue;
            q.push({nextc, {curcopy, curtime+1}});
            visit[nextc][curcopy] = 1;
            dp[nextc] = curtime+1;
        }
    }
        
    cout << dp[N];
}