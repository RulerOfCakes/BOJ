#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N, K;
ll dp[100002];
ll arr[100002];
ll psum[100002];

ll eq(int a)
{
    
    return dp[a - 1] - psum[a];
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];

        psum[i] = psum[i - 1] + arr[i];
    }

    deque<int> dq;
    //dp[i]=max(dp[i], psum[i]-psum[j]+dp[j-1])
    for (int i = 1; i <= N; i++)
    {
        while (!dq.empty() && dq.front() < i - K)
            dq.pop_front();
        while (!dq.empty() && eq(dq.back()) <= eq(i))
            dq.pop_back();
        dq.push_back(i);
        dp[i] = psum[i] + eq(dq.front());
        if (i <= K)
            dp[i] = max(dp[i], psum[i]);
    }
    cout << dp[N];
}