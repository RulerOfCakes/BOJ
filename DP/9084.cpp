#include <bits/stdc++.h>

using namespace std;

int N, M, T;
int dp[100002];

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--){
        cin >> N;
        
        vector<int> v(N, 0);
        for(int i = 0; i < N; i++){
            cin >> v[i];
        }
        cin >> M;
        fill(dp, dp+M+1, 0);
        dp[0]=1;
        for(int i = 0; i < N; i++){
            for(int j = v[i]; j <= M; j++){
                
                dp[j] += dp[j-v[i]];
            }
        }

        cout << dp[M] << '\n';
    }
}