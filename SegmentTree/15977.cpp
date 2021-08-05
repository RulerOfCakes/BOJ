#include <bits/stdc++.h>
//good read : https://codeforces.com/blog/entry/43319
using namespace std;
using ll = long long;
using pi = pair<int,int>;

int N, M, K;

class segtree
{
public:
    vector<int> tree;
    //vector<long long> cnt; // count of lines
    //vector<long long> sum; // sum of squares
    //vector<long long> lazy; // lazy propagataion
    int size;

    segtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        tree.resize(size * 2, 0);
        //lazy.resize(size * 2);
        //cnt.resize(size * 2);
        //sum.resize(size * 2);
    }
    void update(int node, int x)
    {
        int idx = size + node - 1;
        tree[idx]=x;
        idx/=2;
        while (idx)
        {
            tree[idx] = max(tree[idx*2],tree[idx*2+1]);
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
    int getsum(int node, int nStart, int nEnd, int rStart, int rEnd)
    {
        //update_lazy(node, nStart, nEnd);
        if (nEnd < rStart || nStart > rEnd)
            return 0;
        if (rStart <= nStart && rEnd >= nEnd)
            return tree[node];
        int mid = (nStart + nEnd) / 2;
        return max(getsum(node * 2, nStart, mid, rStart, rEnd), getsum(node * 2 + 1, mid + 1, nEnd, rStart, rEnd));
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
const int MAX_N = 200004;
int input[3][MAX_N];
int A[3][MAX_N];
int dp[MAX_N];
vector<tuple<int,int,int>> B;
segtree seg(1);

//pair LIS
int sol(int s, int e){
    if(s==e)return 0;

    int ret=0;
    int mid = (s+e)/2;
    ret=max(ret,sol(s,mid));
    vector<tuple<int,int,int>> tmp;
    
    for(int i = s; i <= e; i++){
        tmp.push_back(make_tuple(get<1>(B[i]),get<2>(B[i]),i));
    }
    //since B was already sorted in order of the 0th element,
    //we first sort in the order of the 1st element
    //and then keep track of the 2nd elements in the segment tree for LIS
    sort(tmp.begin(),tmp.end());
    for(auto T:tmp){
        int x,y,idx;
        tie(x,y,idx)=T;
        dp[idx]=max(dp[idx],1);
        //idx<=mid is already done from sol(s,mid)
        if(idx>mid){
            //since x is already in increasing order we can just count the previous 'y's
            dp[idx]=max(dp[idx],seg.getsum(1,1,seg.size,1,y)+1);
            ret=max(ret,dp[idx]);
        } else {
            //already processed so just insert in the segment tree
            seg.update(y,dp[idx]);
        }
    }
    for(auto T:tmp){
        int x,y,idx;
        tie(x,y,idx)=T;
        //resetting the segment tree for the next computation(dp table persists)
        if(idx<=mid)seg.update(y,0);
    }
    return ret=max(ret,sol(mid+1,e));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c;
    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> input[i][j];
            A[i][j]=input[i][j];
        }
    }
    for(int i = 0;i  < N; i++){
        sort(input[i],input[i]+M);
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            //storing ranks of the original array
            A[i][j]=(lower_bound(input[i],input[i]+M, A[i][j])-input[i])+1;
        }
    }
    //pair LIS
    if(N==3){
        seg=segtree(M);
        for(int i = 0; i < M; i++){
            B.push_back(make_tuple(A[0][i],A[1][i],A[2][i]));
        }
        sort(B.begin(),B.end());
        ll ans = sol(0,M-1);
        cout << ans;
    }
    //normal LIS
    else if(N==2){
        vector<pi> v;
        for(int i = 0; i < M; i++){
            v.push_back({A[0][i],A[1][i]});
        }
        sort(v.begin(),v.end());
        vector<int> ans(1,-1);
        for(int i = 0; i < M; i++){
            tie(a,b)=v[i];
            if(ans.back()<b)ans.push_back(b);
            else *lower_bound(ans.begin(),ans.end(),b)=b;
        }
        cout << ans.size()-1;
    }
    
}