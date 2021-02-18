#include <bits/stdc++.h>

using namespace std;

int N;

int dp[1003];
int arr[1003];
int idx[1003];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> arr[i];
    }
    int ans = 0;
    for(int i = 1; i <= N; i++){
        idx[i] = i;
        for(int j = 1; j <= i; j++){
            if(arr[i] > arr[j]){
                if(dp[j]+1 > dp[i]){
                    dp[i] = dp[j]+1;
                    idx[i] = j;
                }
            }
        }
    }
    int ansidx = 0;
    for(int i = 1; i <= N; i++){
        if(dp[i]+1 > ans){
            ans = dp[i]+1;
            ansidx = i;
        }
    }
    stack<int> s;
    s.push(arr[ansidx]);
    while(ansidx != idx[ansidx]){
        ansidx = idx[ansidx];
        s.push(arr[ansidx]);
    }
    
    cout << ans << '\n';
    while(!s.empty()){
        cout << s.top() << ' ';
        s.pop();
    }
}