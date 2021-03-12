#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N, M;
int arr[1002];
ll dp[1002];


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> arr[i];
    }
    dp[2] = abs(arr[2]-arr[1]);
    for(int i = 3; i <= N; i++){
        for(int j = 1; j < i; j++){
            dp[i] = max(dp[j] + (*max_element(arr+j+1, arr+i+1) - *min_element(arr+j+1, arr+i+1)), dp[i]);
        }
    }
    cout << dp[N];
}