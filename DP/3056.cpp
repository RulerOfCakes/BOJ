#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N;
double val[21][21];
double dp[1<<20+1];

bool eq(double d1, double d2){
    if(abs(d1-d2)<1e-9)return true;
    else return false;
}

double sol(int cx, int bt){
    if(cx==N)return 1;
    double& ret = dp[bt];
    if(!eq(ret,0))return ret;
    for(int i = 0; i < N; i++){
        if(bt&(1<<i))continue;
        int nbt=bt|(1<<i);
        ret=max(ret,sol(cx+1,nbt)*val[cx][i]);
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> val[i][j];
            val[i][j]/=100;
        }
    }
    cout.precision(6);
    cout << fixed << sol(0,0)*100;
}