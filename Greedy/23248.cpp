#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;

int N, M,K;

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >>M>>N>>K;
    vector<pi> v;
    for(int i = 0; i < K; i++){
        int a,b;
        cin >> a >> b;
        v.push_back({a,b});
    }
    sort(v.begin(),v.end());
    vector<vector<int>> dp(1,vector<int>(1,0));
    for(int i = 0; i < K; i++){
        int cy = v[i].second;
        bool fin=0;
        for(int j = 0; j < dp.size(); j++){
            int cur = dp[j].back();
            if(cy>=cur){
                dp[j].push_back(cy);
                fin=1;
                break;
            }
        }
        if(!fin){
            dp.push_back({cy});
        }
    }
    cout << dp.size();
}