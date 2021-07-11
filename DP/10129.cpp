#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N, Q;
int dp[1000002];
int arr[1000002];

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
    }
    cin >> Q;
    vector<int> birds(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> birds[i];
    }
    for (int q = 0; q < Q; q++)
    {
        memset(dp,0,sizeof(dp));
        //min dp[i]
        deque<int> dq;
        int K = birds[q];
        dp[1]=0;
        dq.push_back(1);

        for (int i = 2; i <= N; i++)
        {

            while (!dq.empty() && dq.front() < i - K)
                dq.pop_front();
            dp[i] = dp[dq.front()] + (arr[i] >= arr[dq.front()]);
            while (!dq.empty() &&
                   ((dp[dq.back()] > dp[i]) || 
                   ((dp[dq.back()] == dp[i]) && (arr[dq.back()] < arr[i]))))
                dq.pop_back();
            dq.push_back(i);

            
        }
        cout << dp[N] << '\n';
    }
}