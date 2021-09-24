#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, Q;
vector<ll>v;

//segbeats
struct Node{
    ll max, max2, maxcnt, sum;
};
class segtree {
public:
	vector<Node> tree;
	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2);
	}
    Node init(int node, int nStart, int nEnd){
        if(nStart==nEnd)return tree[node]={v[nStart],-1,1,v[nStart]};
        int mid = (nStart+nEnd)/2;
        return tree[node]=update_data(init(node*2,nStart,mid),init(node*2+1,mid+1,nEnd));
    }
    //merging the two data from n1 and n2
    Node update_data(Node n1, Node n2){
        if(n1.max == n2.max)
            return {n1.max, max(n1.max2,n2.max2), n1.maxcnt+n2.maxcnt, n1.sum+n2.sum};
        if(n1.max>n2.max)swap(n1,n2);
        return {n2.max,max(n1.max,n2.max2),n2.maxcnt,n1.sum+n2.sum};
    }
	void update_lazy(int node, int start, int end) {
		if(start==end)return;
        for(auto i : {node*2, node*2+1}){
            if(tree[node].max<tree[i].max){
                //means that the child hasn't been updated accordingly, so we do it
                tree[i].sum-=tree[i].maxcnt*(tree[i].max-tree[node].max);
                tree[i].max = tree[node].max;
                //the original max values of tree[i] are all updated to the new max
                //therefore the maxcnt remains the same
            }
        }
	}
	void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, ll diff) {
		update_lazy(node, nStart, nEnd);
        //no need for updates in this case
		if (nEnd < rStart || nStart > rEnd || tree[node].max <= diff)return;
        //only update when the new value fits inside max and max2, for easy update
		if (nStart >= rStart && nEnd <= rEnd && tree[node].max2 < diff) {
			tree[node].sum-=tree[node].maxcnt*(tree[node].max-diff);
            tree[node].max=diff;
			update_lazy(node, nStart, nEnd);
			return;
		}
		
		int mid = (nStart + nEnd) / 2;
		update_range(node*2, nStart, mid, rStart, rEnd, diff);
		update_range(node*2+1, mid + 1, nEnd, rStart, rEnd, diff);
		tree[node] = update_data(tree[node * 2], tree[node * 2 + 1]);
	}
    ll getmax(int node, int nStart, int nEnd, int rStart, int rEnd){
        update_lazy(node,nStart,nEnd);
        if(rEnd<nStart||nEnd<rStart)return 0;
        if(rStart<=nStart&&nEnd<=rEnd)return tree[node].max;
        int mid = (nStart+nEnd)/2;
        return max(getmax(node*2,nStart,mid,rStart,rEnd),getmax(node*2+1,mid+1,nEnd,rStart,rEnd));
    }
	long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd) {
		update_lazy(node, nStart, nEnd);
		if (nEnd < rStart || nStart > rEnd) return 0;
		if (rStart <= nStart && rEnd >= nEnd) return tree[node].sum;
		int mid = (nStart + nEnd) / 2;
		return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid+1, nEnd, rStart, rEnd);
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	ll a, b, c;
	cin >> N;
	segtree seg(N+1);
    v=vector<ll>(N+1);
	for(int i = 0;i < N; i++){
        cin >> a;
        v[i+1]=a;
    }
    seg.init(1,1,seg.size);
    cin >> Q;	
	for (int n = 0; n < Q; n++) {
        ll d;
		cin >> a >> b >> c;
        if(a==1){
            cin >> d;
            seg.update_range(1,1,seg.size,b,c,d);
        }
        else if(a==2){
            cout << seg.getmax(1,1,seg.size,b,c) << '\n';
        }
        else{
            cout << seg.getsum(1,1,seg.size,b,c) << '\n';
        }
	}

	
	
}