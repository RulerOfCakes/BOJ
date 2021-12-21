#include <bits/stdc++.h>
using namespace std;
int N;
bool dp[2];
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    string ans="YES";int a;
    for(int i = 1; i <= N; i++){
        cin>>a;
        if(a>2||a-dp[!(i&1)]>1){
            ans="NO";break;
        }
        dp[i&1]=-(a-dp[!(i&1)]);
    }
    if(dp[N&1])ans="NO";
    cout<<ans;
}