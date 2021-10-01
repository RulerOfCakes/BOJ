#include <bits/stdc++.h>

using namespace std;

using ll = long long;
int N, M;
const int MOD = 1999;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    if(N==1){
        cout << 1;
        return 0;
    }
    //describe M as a sum of integers from range [1,N]
    vector<int> ans(max(N+1,M+1));
    
    int ret = 1;
    ans[1]=1;
    for(int i = 2; i < N; i++){
        ans[i]=ans[i-1]*2;
        ans[i]%=MOD;
    }
    ans[N]=ans[N-1]*4-1;
    ans[N]%=MOD;
    for(int i = N+1; i <= M; i++){
        ans[i]=((ans[N-1]*2)%MOD)*ans[i-N];
        ans[i]%=MOD;
        for(int j = 1; j <= N-1; j++){
            ans[i]+=ans[i-j];
            ans[i]%=MOD;
        }
    }
    cout << ans[M];

}