#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N;
int dp[101010][2];
int process(int x, string s){
    switch(s[0]){
        case '+':
        x+=(s[1]-'0');
        return x;
        case '-':
        x-=(s[1]-'0');
        return x;
        case '/':
        x/=(s[1]-'0');
        return x;
        case '*':
        x*=(s[1]-'0');
        return x;
        default:break;
    }
    return x;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    string ans="";
    dp[0][0]=1;dp[0][1]=1;
    for(int i = 1; i <= N; i++){
        string s1,s2;
        cin>>s1>>s2;
        for(int j = 0; j < 2; j++){
            if(dp[i-1][j]>0)
                dp[i][j]=max(process(dp[i-1][j],s1),process(dp[i-1][j],s2));
            if(j&&dp[i-1][j-1]>0){
                dp[i][j]=max(dp[i][j],dp[i-1][j-1]);
            }
        }
        if(!((dp[i][0]>0)||(dp[i][1]>0)))ans="ddong game";
    }
    if(ans.empty()){
        cout<<max(dp[N][0],dp[N][1]);
    }
    else{
        cout<<ans;
    }
}