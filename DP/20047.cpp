#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;

int N, i1, i2;

bool dp[10002][3];
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    string S,T;
    cin >> S;
    cin >> T;
    cin >> i1 >> i2;
    char cc[2]={S[i1],S[i2]};
    string ts;
    for(int i = 0; i < S.length(); i++){
        if(i==i1 || i == i2)continue;
        ts.push_back(S[i]);
    }
    if(ts[0]==T[0]){
        dp[0][0]=1;
    }
    if(ts[0]==T[1]&&T[0]==cc[0]){
        dp[1][1]=1;
    }
    if(ts[0]==T[2]&&T[0]==cc[0]&&T[1]==cc[1]){
        dp[2][2]=1;
    }
    for(int i = 1; i < T.length(); i++){
        for(int j = 0; j < 3; j++){
            if(!dp[i-1][j])continue;
            if(i-j<0)continue;
            if(j==2){
                if(ts[i-j]==T[i]){
                    dp[i][j]=dp[i-1][j];
                }
                continue;
            }
            if(ts[i-j]==T[i]&&dp[i-1][j]){
                dp[i][j]=dp[i-1][j];
            }
            else{
                if(T[i]==cc[j]){
                    dp[i][j+1]=dp[i-1][j];
                }
            }
        }
    }

    if(dp[N-1][2]){
        cout << "YES";
    }
    else{
        cout << "NO";
    }
}