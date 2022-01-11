#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ti= tuple<int,int,int>;

int N,M;
const int INF = 1e9;
int dp[202][202];
vector<ti> edges;

int main() {
    cin.tie(0)->sync_with_stdio(0);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			dp[i][j] = INF;
			if (i == j)dp[i][j] = 0;
		}
	}
	for (int i = 1; i <= M; i++) {
        int a,b,c;
		cin >> a >> b >> c;
        edges.push_back(make_tuple(a,b,c));
		dp[a][b] = min(dp[a][b], c);
        dp[b][a] = min(dp[b][a], c);
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
			}
		}
	}
    int ans=2e9;

	for (int i = 1; i <= N; i++) {
        int tmp=0;
		for(auto [a,b,c] : edges){
            tmp=max(tmp,(dp[i][a]+dp[i][b]+c));
        }
        ans=min(ans,tmp);
	}
    if(ans&1){
        cout << ans/2 << ".5";
    }
    else
        cout << ans/2 << ".0";
}