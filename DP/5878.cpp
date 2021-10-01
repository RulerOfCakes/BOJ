#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N, L;
ll dp[100002];
ll arr[100002];//width
ll height[100002];//height
ll psum[100002];//width partial sum
const ll INF = 1e12;

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
	
	void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, ll diff) {
		
		if (nEnd < rStart || nStart > rEnd)return;
		if (nStart >= rStart && nEnd <= rEnd) {
			tree[node]=max(tree[node],diff);
            return;
		}
		
		int mid = (nStart + nEnd) / 2;
		update_range(node*2, nStart, mid, rStart, rEnd, diff);
		update_range(node*2+1, mid + 1, nEnd, rStart, rEnd, diff);
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}
	
	ll query(int node, int nStart, int nEnd, int rStart, int rEnd){
        if (nEnd < rStart || nStart > rEnd)return 0;
		if(nStart>=rStart&&nEnd<=rEnd)return tree[node];
		int mid = (nStart+nEnd)/2;
		return max(query(node*2,nStart,mid,rStart,rEnd), query(node*2+1,mid+1,nEnd,rStart,rEnd));
	}
	
};

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> L;
    segtree seg(N);
    for (int i = 1; i <= N; i++)
    {
        cin >> height[i] >> arr[i];
        psum[i] = psum[i-1]+arr[i];
        seg.update_range(1,1,seg.size,i,i,height[i]);
        
    }

    //min dp[i]
    deque<int> dq;
    int i;
    for(i = 1; psum[i] <= L; i++){
        while(!dq.empty()&&height[dq.back()]<=height[i])dq.pop_back();
        dq.push_back(i);
        dp[i]=seg.query(1,1,seg.size,1,i);
    }

    for (; i <= N; i++)
    {

        while (!dq.empty() && psum[i]-psum[dq.front()] > L)
            dq.pop_front();
        dp[i]=INF;
        for(int j = 0; j < dq.size(); j++){
            dp[i]=min(dp[i], dp[dq[j]]+seg.query(1,1,seg.size,dq[j]+1,i));
        }
        //dp[i] = dp[dq.front()] + seg.query(1,1,seg.size,dq.front()+1,i);
        cout << dp[i] << '\n';
        
        while (!dq.empty() &&
               height[dq.back()] <= height[i])
            dq.pop_back();
        dq.push_back(i);
    }
    cout << dp[N] << '\n';
}