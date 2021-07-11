#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N, K;
int dp[300002];
char arr[300002];
int diff[300002];


int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
    
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
        if(arr[i]=='H'){
            diff[i] = diff[i-1]-1;
        } else {
            diff[i]=diff[i-1]+1;
        }
    }
    //min dp[i]
    deque<int> dq;
    
    dq.push_back(0);
    
    for (int i = 1; i <= N; i++)
    {
        
        while (!dq.empty() && dq.front() < i - K)
            dq.pop_front();
        dp[i]=dp[dq.front()]+(diff[i]>=diff[dq.front()]);
        while (!dq.empty() && 
        ((dp[dq.back()]>dp[i]) || ((dp[dq.back()]==dp[i])&&(diff[dq.back()] < diff[i]))))
            dq.pop_back();
        dq.push_back(i);
        
        //dp[i]=dp[dq.front()]+(diff[i]>=diff[dq.front()]);
        //cout << dq.front() << '\n';
        //cout << i << ": " << dp[i] << '\n';
    }
    
    
    cout << dp[N];
}