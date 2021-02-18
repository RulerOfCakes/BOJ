#include <bits/stdc++.h>

using namespace std;

int N;

int dp[1000003];
int arr[1000003];
int idx[1000003];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> arr[i];
    }
    dp[1] = 1;
    int ans = 0, ansidx = 0;
    for(int i = 1; i <= N; i++){
        idx[i] = i;
        for(int j = 1; j <= i; j++){
            if(!dp[j] || arr[i] <= arr[dp[j]]){
                if(!dp[j])ansidx = i;
                idx[i] = dp[j-1];
                dp[j] = i;
                ans = max(ans, j);
                break;
            }
        }
    }
    
    stack<int> s;
    s.push(arr[ansidx]);
    while(ansidx != idx[ansidx]){
        ansidx = idx[ansidx];
        s.push(arr[ansidx]);
    }
    if(!s.top())s.pop();
    cout << ans << '\n';
    if(ans == 1){
        cout << arr[1];
        return 0;
    }
    while(!s.empty()){
        cout << s.top() << ' ';
        s.pop();
    }
}