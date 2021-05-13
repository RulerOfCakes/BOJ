#include <bits/stdc++.h>

using namespace std;
int N;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    vector<int> arr(N, 0);
    vector<int> dp(N, 0);
    vector<pair<int, int>> lis(N);
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    dp[0] = arr[0];
    lis[0]={0, arr[0]};
    int midx = 0;
    for(int i = 1; i < N; i++){
        if(dp[midx]<arr[i]){
            dp[++midx]=arr[i];
            lis[i] = {midx, arr[i]};
        } else {
            auto nidx = lower_bound(dp.begin(), dp.begin()+midx, arr[i]);
            *nidx = arr[i];
            lis[i] = {nidx-dp.begin(), arr[i]};
        }
    }
    cout << midx+1 << '\n';
    
    stack<int> s;
    int tmp = midx;
    for(int i = N-1; i >= 0; i--){
        if(tmp<0)break;
        if(tmp==lis[i].first){
            s.push(lis[i].second);
            --tmp;
        }
    }
    while(!s.empty()){
        cout << s.top() << ' ';
        s.pop();
    }

}