#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
int arr[102][102];
ll dp[102][102];

ll sol(int cx, int cy){
    if(cx==N-1&&cy==N-1)return 1;
    else if(cx>N-1||cy>N-1)return 0;
    if(arr[cx][cy]==0)return 0;
    ll& ret=dp[cx][cy];
    if(ret!=-1)return ret;
    ret=0;
    ret+=sol(cx+arr[cx][cy],cy);
    ret+=sol(cx,cy+arr[cx][cy]);
    return ret;
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    for(int i = 0 ; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> arr[i][j];
            dp[i][j]=-1;
        }
    }
    cout << sol(0,0);
}