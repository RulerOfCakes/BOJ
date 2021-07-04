#include <bits/stdc++.h>

using namespace std;
int N, M, K;

class segtree {
public:
	vector<long long> tree;
	
	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2, 0);
		
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
	
	long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd) {
		
		if (nEnd < rStart || nStart > rEnd) return 0;
		if (rStart <= nStart && rEnd >= nEnd) return tree[node];
		int mid = (nStart + nEnd) / 2;
		return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid+1, nEnd, rStart, rEnd);
	}
	
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b, c;
	cin >> N;
	segtree seg(N);
    vector<int> v(N);
    vector<int> sv;
	for (int n = 0; n < N; n++) {
		cin >> v[n];
        sv.push_back(v[n]);
	}
    sort(sv.begin(), sv.end());
    for(int i = 0; i < N; i++){
        int idx = lower_bound(sv.begin(), sv.end(), v[i])-sv.begin();
        seg.update(idx+1, 1);
        cout << i+1 - seg.getsum(1, 1, seg.size, 1, idx) << '\n';
    }
	
}