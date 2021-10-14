#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<long long, long long>;

int N,B;
const int INF = 1e9 + 7;
vector<int> v;
int psum[4002];
int spsum[4002];
double dp[31][4002];
double errors[4002][4002];
double geterror(int x, int y){
    if(y<x)return INF;
    double ret=0, avg=0;
    
    avg=(double)(psum[y]-psum[x-1]) / (y-x+1);
    ret=spsum[y]-spsum[x-1]-2*avg*(psum[y]-psum[x-1])+avg*avg*(y-x+1);
    // for(int i = x; i <= y; i++){
    //     ret+=(v[i]-avg)*(v[i]-avg);
    // }
    return ret;
}
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> B >> N;
    
    v=vector<int>(N+1);
    
   for(int i = 1; i <= N; i++){
       cin >> v[i];
       psum[i]=psum[i-1]+v[i];
       spsum[i]=spsum[i-1]+v[i]*v[i];
   }
   
   for(int i = 1; i <= N; i++){
       for(int j =i; j <= N; j++){
           errors[i][j]=geterror(i,j);
       }
   }
   for(int i = 1; i <= N; i++){
       dp[1][i]=errors[1][i];
   }
   for(int i = 2; i <= N; i++){
       for(int k = 2; k <= B; k++){
           dp[k][i]=INF;
       }
   }
   
   
   for(int i = 1; i <= N; i++){
       for(int j = i; j <= N; j++){
           for(int k = 2; k <= B; k++){
               if(i==j){
                   dp[k][j]=min(dp[k][j],dp[k-1][i]);
               }
               else
                dp[k][j]=min(dp[k][j],dp[k-1][i]+errors[i+1][j]);
           }
       }
   }
   
   cout << fixed;
   cout.precision(6);
   cout << dp[B][N];
}