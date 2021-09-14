#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using ppi = pair<pi, pi>;

int W,H,K;
const int INF = 1e5 + 1;

int arr1[101][101];


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c, d;
    for(int i = 0;i  < 4; i++){
        cin >> a >> b >> c >> d;
        for(int i = a; i < c; i++){
            for(int j = b; j < d; j++){
                arr1[i][j]++;
            }
        }
    }
    int ans =0 ;

    for(int i = 0 ;i <= 100; i++){
        for(int j = 0; j <= 100; j++){
            if(arr1[i][j])ans++;
        }
    }
    cout << ans;
    
}