#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int INF = 1e5;

ll X, A, B;
bool ok[11];
ll dp[100005][12];
//n:remaining digits, prefix:current prefix
ll sol( int n, ll prefix){
   
    ll maxt=prefix,mint=prefix;
    for(int i = 0; i < n; i++)mint*=10;
    for(int i = 0; i < n; i++)maxt=maxt*10+9;
    
    //out of range
    if(maxt<A||mint>B)return 0;
    //in range && finished
    if(n==0)return prefix%X==0;

    bool memo = mint>=A&&maxt<=B;

    ll& ref=dp[prefix%X][n];
    if(memo&&ref!=-1)return ref;

    ll ret=0;
    for(int digit=0; digit<10; digit++){
        //elongating the prefix || reducing n
        if(ok[digit]||(digit==0&&prefix==0)){
            ret+=sol(n-1,prefix*10+digit);
        }
    }
    if(memo)ref=ret;

    return ret;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    
    cin >> X >> A >> B;
    string s;
    cin >> s;
    for(char c : s){
        ok[c-'0']=1;
    }    
    ll ans = 0;
    
    if(X >= INF){
        //less than 1mil cases
        for(ll x = X; x <= B; x+=X){
            bool v = true;
            for(ll y = x; v && y; y/=10){
                if(!ok[y%10])v=false;
            }
            if(v&&x>=A)ans++;
        }
    }else{
        //dp
        memset(dp,-1,sizeof(dp));
        ans=sol(12,0);
    } 
    cout << ans;
}