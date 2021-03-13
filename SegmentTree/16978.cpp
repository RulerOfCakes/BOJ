#include <bits/stdc++.h>

using namespace std;
int N, M, K;

class segtree {
public:
	vector<long long> tree;
	//vector<long long> cnt; // count of lines
	//vector<long long> sum; // sum of squares
	vector<long long> lazy; // lazy propagataion
	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2, 0);
		lazy.resize(size * 2);
		//cnt.resize(size * 2);
		//sum.resize(size * 2);
	}
	void update(int node, long long x) {
		int idx = size + node - 1;
		long long diff = x - tree[idx];
		while (idx) {
			tree[idx] += diff;
			idx /= 2;
		}
	}
	void update_lazy(int node, int start, int end) {
		if (!lazy[node])return;
		tree[node] += lazy[node] * (end - start + 1);
		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
	}
	void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, int diff) {
		update_lazy(node, nStart, nEnd);
		if (nEnd < rStart || nStart > rEnd)return;
		if (nStart >= rStart && nEnd <= rEnd) {
			lazy[node] = diff;
			update_lazy(node, nStart, nEnd);
			return;
		}
		
		int mid = (nStart + nEnd) / 2;
		update_range(node*2, nStart, mid, rStart, rEnd, diff);
		update_range(node*2+1, mid + 1, nEnd, rStart, rEnd, diff);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
	long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd) {
		update_lazy(node, nStart, nEnd);
		if (nEnd < rStart || nStart > rEnd) return 0;
		if (rStart <= nStart && rEnd >= nEnd) return tree[node];
		int mid = (nStart + nEnd) / 2;
		return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid+1, nEnd, rStart, rEnd);
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b, c, d;
	cin >> N;
	segtree seg(N);
	for (int n = 0; n < N; n++) {
		cin >> a;
		seg.update(n+1, a);
	}
    vector<pair<int, int>> q1;
    vector<pair<pair<int, int>, pair<int, int>>> q2;
    int q2size = 0;
	cin >> M;
	for (int i = 0; i < M; i ++ ) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c;
			q1.push_back({b, c});
		}
		if (a == 2) {
			cin >> b >> c >> d;
			q2.push_back({{b, q2size}, {c, d}});
            q2size++;
		}
	}
    vector<long long> ans(q2.size());
    sort(q2.begin(), q2.end());
    int q1idx = 0;
    for(int i = 0; i < q2.size(); i++){
        int curq = q2[i].first.first, curqidx = q2[i].first.second, start = q2[i].second.first, end = q2[i].second.second;
        while(q1idx < curq){
            seg.update(q1[q1idx].first, q1[q1idx].second);
            q1idx++;
        }
        ans[curqidx]=seg.getsum(1, 1, seg.size, start, end);
    }
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << '\n';
    }
}