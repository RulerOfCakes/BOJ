#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N, D;
ll dp[100002];
ll arr[100002];
const ll INF = 1e14+3;


int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> D;
    
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
        
    }
    //max dp[i]
    deque<int> dq;
    ll ans = -INF;
    for (int i = 1; i <= N; i++)
    {
        
        while (!dq.empty() && dq.front() < i - D)
            dq.pop_front();
        if(!dq.empty()){
            dp[i] = max(arr[i], dp[dq.front()]+arr[i]);
        } else {
            //we can start anywhere
            dp[i]=arr[i];
        }
        while (!dq.empty() && dp[dq.back()] <= dp[i])
            dq.pop_back();
        dq.push_back(i);
        //we can end anywhere
        ans=max(ans,dp[i]);
    }
    
    
    cout << ans;
}