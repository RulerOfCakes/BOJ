#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int,int>;

int N;
const int INF = 1e9+7;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b;
	cin >> N;
	vector<pi> lines;
	for(int i = 0; i < N; i++){
		cin >> a >> b;
		lines.push_back(make_pair(a,b));
	}
	sort(lines.begin(),lines.end());

	int ans = 0, l = -INF, r = -INF;
	for(int i =0; i < N; i++){
		if(r<lines[i].first){
			ans+=r-l;
			l=lines[i].first;
			r=lines[i].second;
		}
		else{
			r=max(r,lines[i].second);
		}
	}
	ans+=r-l;
	cout << ans;
}