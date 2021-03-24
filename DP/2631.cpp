#include <bits/stdc++.h>

using namespace std;

int N;
int dp[202];

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    vector<int> v(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        cin >> v[i + 1];
    }
    //unmoved elements should form an increasing subsequence
    //therefore the answer is N - len(LIS)
    dp[1] = v[1];
    int ans = 1;
    for(int i = 2; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(v[i] < dp[j]){
                dp[j] = v[i];
                break;
            }
            else if(!dp[j]){
                dp[j] = v[i];
                ans = max(ans, j);
                break;
            }
        }
    }
    cout << N-ans;
}