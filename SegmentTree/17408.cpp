#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
int N, M, K;

pll maxpair(pll a, pll b){
    ll x, y;
    x = max(a.second, b.second);
    if(a.first >= b.first){
        y = max(b.first, x);
        a.second = y;
    }
    else{
        y = max(a.first, x);
        a.first = b.first;
        a.second = y;
    }
    return a;
}

class segtree {
public:
	vector<pll> tree;
	//vector<long long> cnt; // count of lines
	//vector<long long> sum; // sum of squares
	//vector<long long> lazy; // lazy propagataion
	int size;
	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2);
		//cnt.resize(size * 2);
		//sum.resize(size * 2);
	}
	void update(int node, long long x) {
		int idx = size + node - 1;
		tree[idx].first = x;
        int mid = idx / 2;
		while (idx) {
			tree[idx/2] = maxpair(tree[idx], tree[idx+1]);
            idx >>= 1;
		}
	}
	
	ll getAns(int start, int end){
        pll ans = {0, 0};
        start += size, end += size;
        while(start <= end){
            if(start&1){
                ans = maxpair(ans, tree[start]);
                start++;
            }
            if(~end&1){
                ans = maxpair(ans, tree[end]);
                end--;
            }
            start >>= 1, end >>= 1;
        }
        return ans.first + ans.second;
    }
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b, c;
	cin >> N;
	segtree seg(N);
	for (int n = 0; n < N; n++) {
		cin >> a;
		seg.update(n, a);
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c;
			seg.update(b-1, c);
		}
		if (a == 2) {
			cin >> b >> c;
			cout << seg.getAns(b-1, c-1) << "\n";
		}
	}
}