#include <bits/stdc++.h>

using namespace std;

bool dp[5002][5002];
int psum[5002][5002];

int val(char c){
    if(c=='(')return 1;
    else return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string s;int ans = 0;
    cin >> s;
    int N = s.length();
    for(int i = 0;i < N-1; i++){
        if(s[i]!=s[i+1]){
            //ans++;
            dp[i][i+1]=1;
    
        }
    }

    for(int i = N-2;i>=0; i--){
        for(int j = i+1 ;j < N; j++){
            if(i==j||j==i+1)continue;
            dp[i][j]=(s[i]!=s[j])&&dp[i+1][j-1];
        }
    }
    

    for(int i = N-2; i >=0; i--){
        psum[i][i]=val(s[i]);
        if(psum[i][i]<0)continue;
        for(int j = i+1; j < N; j++){
            psum[i][j]=psum[i][j-1]+val(s[j]);
            if(psum[i][j]<0)break;
            if(psum[i][j]==0&&dp[i][j]){
                ans++;
                //cout << i << ' ' << j << '\n';
            }
        }
    }
    cout << ans;
}