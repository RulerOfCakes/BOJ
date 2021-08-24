#include <bits/stdc++.h>

using namespace std;

int N, M;
int dp[502][502];
int tracer[502][502];

int A[502],B[502];


int LIS(int pa, int pb){
    if(pa>N||pb>M)return 0;
    int& ret = dp[pa][pb];
    if(ret!=-1)return ret;

    ret=1;
    tracer[pa][pb]=(N+1)*1000+M+1;
    for(int i = pa+1; i <= N; i++){
        if(A[pa]>=A[i])continue;
        for(int j = pb+1; j <= M; j++){
            if(A[i]==B[j]){
                int tmp = LIS(i,j)+1;
                if(ret<tmp){
                    ret=tmp;
                    tracer[pa][pb]=i*1000+j;
                }
                break;
            }
        }
    }
    return ret;
}

void trace(int pa, int pb){
    if(pa>N||pb>M)return;
    cout << A[pa] << ' ';
    trace(tracer[pa][pb]/1000,tracer[pa][pb]%1000);
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> A[i+1];
    }
    cin >> M;
    for(int i = 0; i < M; i++){
        cin >> B[i+1];
    }
    memset(dp,-1,sizeof(dp));
    int ans = 0, start=-1;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            if(A[i]==B[j]){
                int tmp=LIS(i,j);
                if(ans<tmp){
                    ans=tmp;
                    start=i*1000+j;
                }
                break;
            }
        }
    }
    cout << ans << '\n';
    if(start!=-1)trace(start/1000,start%1000);
}