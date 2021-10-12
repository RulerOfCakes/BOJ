#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<long long, long long>;

int N,T;
const int INF = 1e9 + 7;

int ccw(pi p1, pi p2)
{
    long long ret = p1.first * p2.second - p2.first * p1.second;
    if (ret < 0)
        return -1;
    else if (ret > 0)
        return 1;
    else
        return 0;
}

int ccw(pi p1, pi p2, pi p3)
{
    return ccw({p1.first - p3.first, p1.second - p3.second}, {p2.first - p3.first, p2.second - p3.second});
}

bool check(pi p1, pi p2, pi p3, pi inc){
    if(ccw(inc,p1,p2)!=1)return false;
    if(ccw(inc,p2,p3)!=1)return false;
    if(ccw(inc,p3,p1)!=1)return false;
    return true;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<pi> arr;
    cin >> N;
    vector<vector<vector<int>>> dp(N+1,vector<vector<int>>(N+1,vector<int>(N+1,0)));
    pi base = {INF,INF};
    int idx=0;
    for(int i = 0; i < N; i++){
        int a,b;
        cin >> a >> b;
        arr.push_back({a,b});
        if(b<base.second){
            base={a,b};
            idx=i;
        }
    }
    //lowest point on arr[0];
    swap(arr[0],arr[idx]);
    int ans = 0;
    //sort by ccw order
    sort(arr.begin()+1,arr.end(),[&](pi p1, pi p2){
        int val = ccw(arr[0], p1, p2);
        if (val != 0)
            return val > 0 ? true : false;
        if (p1.first == p2.first)
            return p1.second < p2.second;
        return p1.first < p2.first;
    });
    for(int i = 1; i < N; i++){
        for(int j = i+1; j < N; j++){
            int& cur = dp[0][i][j];
            for(int k = i+1; k < j; k++){
                if(!check(arr[0],arr[i],arr[j],arr[k]))continue;
                cur++;
            }
            if(cur)ans++;
        }
    }

    for(int i = 1; i < N; i++){
        for(int j = i+2; j < N; j++){
            for(int k = i+1; k < j; k++){
                int& cur = dp[i][k][j];
                if(!check(arr[0],arr[i],arr[j],arr[k]))
                    cur = dp[0][i][k]+dp[0][k][j]-dp[0][i][j];
                else
                    cur = dp[0][i][j]-dp[0][i][k]-dp[0][k][j]-1;
                
                if(cur)ans++;
            }
        }
    }

    cout << ans;
}