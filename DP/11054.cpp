#include <bits/stdc++.h>

using namespace std;

int N;

int dp1[1003];
int dp2[1003];
int arr[1003];
int rarr[1003];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> arr[i];
        rarr[N+1-i] = arr[i];
    }
    int ans = 0;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= i; j++){
            if(arr[i] > arr[j]){
                dp1[i] = max(dp1[i], dp1[j] + 1);
            }
        }
    }
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= i; j++){
            if(rarr[i] > rarr[j]){
                dp2[i] = max(dp2[i], dp2[j] + 1);
            }
        }
    }
    for(int i = 1; i <= N; i++){
        ans = max(ans, dp1[i]+dp2[N+1-i]);
    }
    cout << ans + 1;
}