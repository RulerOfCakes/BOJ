#include <bits/stdc++.h>
using namespace std;
int N,M;
bool equals(char c1, char c2){
    if(c1==c2)return true;
    if(c1=='i'){
        if(c2=='j'||c2=='l')return true;
        else return false;
    }
    else if(c1=='v'){
        if(c2=='w')return true;
        else return false;
    }
    else{
        return c1==c2;
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M;
    vector<vector<int>>dp(N+1,vector<int>(M+1));
    string s1,s2;
    cin>>s1>>s2;
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= M; j++){
            if(!i)dp[i][j]=j;
            else if(!j)dp[i][j]=i;
            else
            dp[i][j]=min({dp[i-1][j]+1,dp[i][j-1]+1,dp[i-1][j-1]+!equals(s1[i-1],s2[j-1])});
        }
    }

    cout << dp[N][M];
}