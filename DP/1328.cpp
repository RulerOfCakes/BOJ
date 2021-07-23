#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 1000000007;
ll dp[102][102][102];

int N, L, R;

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> L >> R;
    dp[1][1][1]=1;
    
    for(int i = 2; i <= N; i++){
        for(int j = 1; j <= L; j++){
            for(int k = 1; k <= R; k++){
                dp[i][j][k]=(ll)dp[i-1][j-1][k]+dp[i-1][j][k-1]+dp[i-1][j][k]*(i-2);
                dp[i][j][k]%=MOD;
            }
        }
    }
    cout << dp[N][L][R]%MOD;

}