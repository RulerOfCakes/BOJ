#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M;

class segtree {
public:
	vector<long long> tree;
	int size;
	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2, 0);
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
	cin >> N >> M;
    segtree seg(N+2);
    for(int i = 0; i < M; i++){
        int a,b,c;
        cin >> a >> b >> c;
        if(a==0){
            if(b>c)swap(b,c);
            cout << seg.getsum(1,1,seg.size,b,c) << '\n';
        }
        else if(a==1){
            seg.update(b,c);
        }
    }
}