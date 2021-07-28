#include <bits/stdc++.h>

using namespace std;

int K;
int T;
int dp[502][502];
int sum[502];


int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--){
        cin >> K;
        memset(dp, 0, sizeof(dp));
        fill(sum, sum+K+1, 0);
        vector<int> pages(K+1, 0);
        
        for(int i = 1; i <= K; i++){
            cin >> pages[i];
            
            sum[i] = sum[i-1]+pages[i];
        }
        //range of numbers
        for(int i = 1; i < K; i++){
            //starting idx
            for(int j = 1; j+i <= K; j++){
                //ending idx
                int e = j+i;
                int temp = INT_MAX;
                int psum=sum[e]-sum[j-1];
                for(int k = j; k < e; k++){
                    temp = min(temp, dp[j][k]+dp[k+1][e]+psum);
                }
                //if(temp==INT_MAX)continue;
                dp[j][e] = temp;
            }
        }
        cout << dp[1][K] << '\n';
    }
}