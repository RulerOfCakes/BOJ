#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int INF = INT_MAX;
int N, M;
int leftt[100002], rightt[100002];


class segtree {
public:
    vector<vector<int>> otree;
    vector<ll> tree;
    vector<ll> lazy;
    
    int size;

    segtree(int n) {
        for (size = 1; size <= n; size *= 2);
        tree.resize(size * 2);
        lazy.resize(size * 2);
        otree.resize(n + 1);
    }
    void dfs(int now, int& o) {
        leftt[now] = ++o;
        for (int next : otree[now]) {
            dfs(next, o);
        }
        rightt[now] = o;
    }
    void update(int node, long long x) {
		int idx = size + node - 1;
		long long diff = x;
		while (idx) {
			tree[idx] += diff;
			idx /= 2;
		}
	}
    // void update_lazy(int node, int nStart, int nEnd) {
    //     if (!lazy[node])return;
    //     tree[node] += lazy[node] * (nEnd - nStart + 1);
    //     if (nStart != nEnd) {
    //         lazy[node * 2] += lazy[node];
    //         lazy[node * 2 + 1] += lazy[node];
    //     }
    //     lazy[node] = 0;
    // }
    // void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, ll diff) {
    //     update_lazy(node, nStart, nEnd);
    //     if (nStart > rEnd || rStart > nEnd)return;
    //     if (nStart >= rStart && rEnd >= nEnd) {
    //         tree[node] += (nEnd - nStart + 1) * diff;
    //         if(nStart != nEnd) {
    //             lazy[node * 2] += diff;
    //             lazy[node * 2 + 1] += diff;
    //         }
    //         return;
    //     }
    //     int mid = (nStart + nEnd) / 2;
    //     update_range(node * 2, nStart, mid, rStart, rEnd, diff);
    //     update_range(node * 2 + 1, mid + 1, nEnd, rStart, rEnd, diff);
    //     tree[node] = tree[node * 2] + tree[node * 2 + 1];
    // }
    long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd) {
		//update_lazy(node, nStart, nEnd);
		if (nEnd < rStart || nStart > rEnd) return 0;
		if (rStart <= nStart && rEnd >= nEnd) return tree[node];
		int mid = (nStart + nEnd) / 2;
		return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid+1, nEnd, rStart, rEnd);
	}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c;
    cin >> N >> M;
    segtree seg(N);
    
    for (int i = 1; i <= N; i++) {
        cin >> a;
        if (a == -1) continue;
        //grouping with parents
        seg.otree[a].push_back(i);
    }
    //labelling
    //starting from root(1)
    int o = 0;
    seg.dfs(1, o);
    for (int i = 0; i < M; i++) {
        cin >> a;
        if (a == 1) { 
            cin >> b >> c;
            //seg.update_range(1, 1, N, leftt[b], leftt[b], c);
            seg.update(leftt[b],c);
            //cout << leftt[b] << "\n\n";
        }
        else if (a == 2) {
            cin >> b;
            cout << seg.getsum(1, 1, seg.size, leftt[b],rightt[b]) << "\n";
        }
    }
}