#include <bits/stdc++.h>

using namespace std;

int N, M;
bool dp[2002][2002];

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    vector<int> v(N, 0);
    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }
    cin >> M;
    for(int i = 0; i < N; i++){
        dp[i][i]=1;
        dp[i][i+1]=(v[i]==v[i+1]);
    }
    for(int i = 2; i < N; i++){
        for(int j = 0; j < N-i; j++){
            dp[j][i+j]=((dp[j+1][j+i-1]) && (v[j]==v[j+i]));
        }
    }
    while(M--){
        int s, e;
        cin >> s >> e;
        cout << dp[s-1][e-1] << '\n';
    }
}