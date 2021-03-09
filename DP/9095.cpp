#include <bits/stdc++.h>

using namespace std;

int N, T;
int dp1[12];
int dp2[12];
int dp3[12];


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--){
        cin >> N;
        dp1[1] = 1;
        dp2[2] = 1;
        dp3[3] = 1;
        for(int i = 2; i <= N; i++){
            dp1[i] = dp1[i-1] + dp2[i-1] + dp3[i-1];
            if(i > 2)
            dp2[i] = dp1[i-2] + dp2[i-2] + dp3[i-2];
            if(i > 3)
            dp3[i] = dp1[i-3] + dp2[i-3] + dp3[i-3];
        }
        cout << dp1[N]+dp2[N]+dp3[N] << '\n';
    }
}