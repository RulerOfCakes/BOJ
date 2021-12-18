#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, K;

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
	cin >> N >> K;
    vector<int> trees(N+1);
    segtree seg(N+1);
    //for each point that changes color we add 1
    for(int i = 1; i <= N; i++){
        cin >> trees[i];
        if(trees[i]!=trees[i-1])seg.update(i,1);
    }
    while(K--){
        int t,a,b;
        cin>>t>>a>>b;
        if(t==1){
            //we have to buy one at A initially, so skip A and add 1
            cout << seg.getsum(1,1,seg.size,a+1,b)+1<<'\n';
        }
        else{
            trees[a]=b;
            //update values of a, a+1 accordingly
            if(a>1){
                ll aq=seg.getsum(1,1,seg.size,a,a);
                if(aq&&trees[a]==trees[a-1])seg.update(a,0);
                else if(!aq&&trees[a]!=trees[a-1])seg.update(a,1);
            }
            if(a<N){
                ll aq=seg.getsum(1,1,seg.size,a+1,a+1);
                if(aq&&trees[a]==trees[a+1])seg.update(a+1,0);
                else if(!aq&&trees[a]!=trees[a+1])seg.update(a+1,1);
            }
        }
    }
}