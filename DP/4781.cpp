#include <bits/stdc++.h>

using namespace std;

int N;
double M;
int dp[10002];

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while(true){
        cin >> N >> M;
        if(N==0 && M == 0.00){
            break;
        }
        vector<pair<int, double>> candies(N);
        
        for(int i = 0; i < N; i++){
            int a;double b;
            cin >> a >> b;
            candies[i] = {a, b};
        }
        int lm = (int)(floor(M*100+0.5)+0.5);
        fill(dp, dp+lm+1, 0);
        for(int i = 0; i < N; i++){
            int cc = candies[i].first, cm = (int)(floor(candies[i].second*100+0.5)+0.5);
            for(int j = cm; j <= lm; j++){
                dp[j]=max(dp[j], dp[j-cm]+cc);
            }
        }

        cout << dp[lm] << '\n';
    }
}