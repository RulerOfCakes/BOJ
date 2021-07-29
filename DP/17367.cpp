#include <bits/stdc++.h>

using namespace std;

int N;

double dp[7][7][1002];

int prize(int a, int b, int c){
    vector<int> v={a,b,c};
    sort(v.begin(),v.end());
    a=v[0],b=v[1],c=v[2];
    if(a==b&&b==c){
        return 10000+a*1000;
    }
    else if(a==b||b==c){
        return 1000+b*100;
    }
    else{
        return 100*c;
    }
}

//a,b -> recent two rolls, n-> remaining throws
double sol(int a, int b, int n){
    if(!n)return 0;
    if(dp[a][b][n]!=-1){
        return dp[a][b][n];
    }
    double& ret = dp[a][b][n];
    double sum = 0;
    for(int i = 1; i <= 6; i++){
        sum += max((double)prize(a,b,i),sol(b,i,n-1));
    }
    return ret=sum/6;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    double ans = 0;
    //do not use memset for (double) arrays
    for(int i = 1; i <= 6; i++){
        for(int j = 1; j <= 6; j++){
            for(int k = 0; k <= N; k++){
                dp[i][j][k]=-1;
            }
        }
    }
    for(int i = 1; i <= 6; i++){
        for(int j = 1; j <= 6; j++){
            ans += sol(i,j,N-2);
        }
        
    }
    cout << fixed; cout.precision(6);
    cout << ans/36;
}