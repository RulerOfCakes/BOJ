#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, K;

class segtree {
public:
	vector<long long> tree;
	//vector<long long> cnt; // count of lines
	//vector<long long> sum; // sum of squares
	//vector<long long> lazy; // lazy propagataion
	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2, 0);
		//lazy.resize(size * 2);
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
	// void update_lazy(int node, int start, int end) {
	// 	if (!lazy[node])return;
	// 	tree[node] += lazy[node] * (end - start + 1);
	// 	if (start != end) {
	// 		lazy[node * 2] += lazy[node];
	// 		lazy[node * 2 + 1] += lazy[node];
	// 	}
	// 	lazy[node] = 0;
	// }
	// void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, int diff) {
	// 	update_lazy(node, nStart, nEnd);
	// 	if (nEnd < rStart || nStart > rEnd)return;
	// 	if (nStart >= rStart && nEnd <= rEnd) {
	// 		lazy[node] = diff;
	// 		update_lazy(node, nStart, nEnd);
	// 		return;
	// 	}
		
	// 	int mid = (nStart + nEnd) / 2;
	// 	update_range(node*2, nStart, mid, rStart, rEnd, diff);
	// 	update_range(node*2+1, mid + 1, nEnd, rStart, rEnd, diff);
	// 	tree[node] = tree[node * 2] + tree[node * 2 + 1];
	// }
	long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd) {
		// update_lazy(node, nStart, nEnd);
		if (nEnd < rStart || nStart > rEnd) return 0;
		if (rStart <= nStart && rEnd >= nEnd) return tree[node];
		int mid = (nStart + nEnd) / 2;
		return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid+1, nEnd, rStart, rEnd);
	}
	// ll query(ll val, int node, int nStart, int nEnd){
	// 	update_lazy(node, nStart, nEnd);
	// 	if(nStart==nEnd)return nStart;
	// 	int mid = (nStart+nEnd)/2;
	// 	if(val<=tree[node*2]){
	// 		return query(val, node*2, nStart, mid);
	// 	}
	// 	else return query(val-tree[node*2], node*2+1, mid+1, nEnd);
	// }
	
};

vector<pair<int,int>> arr;
vector<pair<pair<int,int>,pair<int,int>>> q;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	cin >> N;
	
	for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        arr.push_back({a,i+1});
        
    }
    cin >> M;
    for(int i  =0; i < M; i++){
        int a,b,c;
        cin >> a >> b >> c;
        q.push_back({{c,i},{a,b}});
        
    }
    sort(arr.begin(),arr.end(),greater<pair<int,int>>());
    
    sort(q.begin(),q.end(),greater<pair<pair<int,int>,pair<int,int>>>());
    vector<ll> ans(M);
    int idx=0;
	segtree seg(N+1);
    for(int i = 0; i < M; i++){
        int cx = q[i].first.first, sy = q[i].second.first,ey=q[i].second.second;
        int qidx = q[i].first.second;
        while(idx<arr.size()&&arr[idx].first>cx){
            seg.update(arr[idx].second, 1);
            idx++;
        }
        ans[qidx]=seg.getsum(1,1,seg.size,sy,ey);
    }
    for(int i = 0;i  < M; i++){
        cout << ans[i] << '\n';
    }
}