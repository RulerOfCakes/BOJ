#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, Q;
vector<ll>v;

//segbeats
struct Node{
    ll max, min, sum;
};
ll fsqrt(ll x){
    return floor(sqrt(x));
}
class segtree {
public:
	vector<Node> tree;
    vector<ll> lazys, lazyr;
	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2);
        lazys.resize(size*2);
        lazyr.resize(size*2);
	}
    Node init(int node, int nStart, int nEnd){
        if(nStart==nEnd)return tree[node]={v[nStart],v[nStart],v[nStart]};
        int mid = (nStart+nEnd)/2;
        return tree[node]=update_data(init(node*2,nStart,mid),init(node*2+1,mid+1,nEnd));
    }
    //merging the two data from n1 and n2
    Node update_data(Node n1, Node n2){
        return {max(n1.max,n2.max),min(n1.min,n2.min),n1.sum+n2.sum};
    }
	void update_lazy(int node, int start, int end) {
		if(!lazys[node]&&!lazyr[node])return;
        if(!lazyr[node]){
            //normal lazy sum update
            tree[node].max+=lazys[node];
            tree[node].min+=lazys[node];
            tree[node].sum+=lazys[node]*(end-start+1);
            if(end!=start){
                lazys[node*2]+=lazys[node];
                lazys[node*2+1]+=lazys[node];
            }
        }else{
            //sqrt update as well
            //since lazyr will only have a value when fsqrt(min)==fsqrt(max)
            //we can easily update the original values as the following
            tree[node].max=tree[node].min=lazys[node]+lazyr[node];
            tree[node].sum = (end-start+1)*(lazys[node]+lazyr[node]);
            if(start!=end){
                lazys[node*2]=lazys[node];
                lazys[node*2+1]=lazys[node];
                lazyr[node*2+1]=lazyr[node];
                lazyr[node*2]=lazyr[node];
            }
        }
        lazys[node]=lazyr[node]=0;
	}
	void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, ll diff) {
		update_lazy(node, nStart, nEnd);
        //no need for updates in this case
		if (nEnd < rStart || nStart > rEnd)return;
        //only update when the new value fits inside max and max2, for easy update
		if (nStart >= rStart && nEnd <= rEnd) {
			lazys[node]=diff;
			update_lazy(node, nStart, nEnd);
			return;
		}
		
		int mid = (nStart + nEnd) / 2;
		update_range(node*2, nStart, mid, rStart, rEnd, diff);
		update_range(node*2+1, mid + 1, nEnd, rStart, rEnd, diff);
		tree[node] = update_data(tree[node * 2], tree[node * 2 + 1]);
	}
    void update_sqrt(int node, int nStart, int nEnd, int rStart, int rEnd){
        update_lazy(node,nStart,nEnd);
        if(rEnd<nStart||nEnd<rStart)return;
        if(rStart<=nStart&&nEnd<=rEnd){
            if(fsqrt(tree[node].min)==fsqrt(tree[node].max)){
                //this range can be grouped together for lazy propagation
                lazyr[node]=fsqrt(tree[node].max);
                update_lazy(node,nStart,nEnd);
                return;
            }
            else if(tree[node].min+1==tree[node].max){
                //in this case we can assure that only two values exist within this range
                //either min or max, and their fsqrt() values should also differ by 1
                //because of this, the value of fsqrt(min)-min == fsqrt(max)-max
                //therefore we can update the lazy sum accordingly in this case
                lazys[node]=fsqrt(tree[node].min)-tree[node].min;
                update_lazy(node,nStart,nEnd);
                return;
            }
        }
        int mid = (nStart+nEnd)/2;
        update_sqrt(node*2,nStart,mid,rStart,rEnd);
        update_sqrt(node*2+1,mid+1,nEnd,rStart,rEnd);
        tree[node]=update_data(tree[node*2],tree[node*2+1]);
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
	cin >> N >> Q;
	segtree seg(N+1);
    v=vector<ll>(N+1);
	for(int i = 0;i < N; i++){
        cin >> a;
        v[i+1]=a;
    }
    seg.init(1,1,seg.size);
    	
	for (int n = 0; n < Q; n++) {
        ll d;
		cin >> a >> b >> c;
        if(a==1){
            cin >> d;
            seg.update_range(1,1,seg.size,b,c,d);
        }
        else if(a==2){
            seg.update_sqrt(1,1,seg.size,b,c);
        }
        else{
            cout << seg.getsum(1,1,seg.size,b,c) << '\n';
        }
	}

	
	
}