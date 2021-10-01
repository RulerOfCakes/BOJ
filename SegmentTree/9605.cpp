#include <bits/stdc++.h>
//good read : https://codeforces.com/blog/entry/43319
using namespace std;
using ll = long long;
using pi = pair<int, int>;

int N, M, aA, bB;

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
        tree[idx] = x;
        idx /= 2;
        while (idx)
        {
            tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
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
const int MAX_N = 300004;
int input[3][MAX_N];
int A[3][MAX_N];
int dp[MAX_N];
vector<tuple<int, int, int>> B;
segtree seg(1);

//pair LIS
int sol(int s, int e)
{
    if (s == e)
        return 0;

    int ret = 0;
    int mid = (s + e) / 2;
    ret = max(ret, sol(s, mid));
    vector<tuple<int, int, int>> tmp;

    for (int i = s; i <= e; i++)
    {
        tmp.push_back(make_tuple(get<1>(B[i]), get<2>(B[i]), i));
    }
    //since B was already sorted in order of the 0th element,
    //we first sort in the order of the 1st element
    //and then keep track of the 2nd elements in the segment tree for LIS
    sort(tmp.begin(), tmp.end());
    for (auto T : tmp)
    {
        int x, y, idx;
        tie(x, y, idx) = T;
        dp[idx] = max(dp[idx], 1);
        //idx<=mid is already done from sol(s,mid)
        if (idx > mid)
        {
            //since x is already in increasing order we can just count the previous 'y's
            dp[idx] = max(dp[idx], seg.getsum(1, 1, seg.size, 1, y) + 1);
            ret = max(ret, dp[idx]);
        }
        else
        {
            //already processed so just insert in the segment tree
            seg.update(y, dp[idx]);
        }
    }
    for (auto T : tmp)
    {
        int x, y, idx;
        tie(x, y, idx) = T;
        //resetting the segment tree for the next computation(dp table persists)
        if (idx <= mid)
            seg.update(y, 0);
    }
    return ret = max(ret, sol(mid + 1, e));
}

int ra, rb, rc = ~(1 << 31), mM = (1 << 16) - 1;
int r()
{
    ra = 36969 * (ra & mM) + (ra >> 16);
    rb = 18000 * (rb & mM) + (rb >> 16);
    return (rc & ((ra << 16) + rb)) % 1000000;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a, b, c;
    while (true)
    {
        int ans;
        cin >> M >> N >> aA >> bB;
        if (!M && !N && !aA && !bB)
            break;
        ra = aA;
        rb = bB;
        rc = ~(1 << 31);
        mM = (1 << 16) - 1;
        memset(input, 0, sizeof(input));
        memset(A, 0, sizeof(A));
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cin >> input[j][i];
                A[j][i] = input[j][i];
            }
        }
        for (int i = M; i < M + N; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                input[j][i] = r();
                A[j][i] = input[j][i];
            }
        }
        if (M + N == 1)
            ans = 1;
        else if (M + N == 2)
        {
            ans = 1;
            if ((input[0][0] < input[0][1]) && (input[1][0] < input[1][1]) && (input[2][0] < input[2][1]))
                ans = 2;
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                sort(input[i], input[i] + M + N);
            }

            for (int i = 0; i < 3; i++)
            {
                map<int, int> mp;
                for (int j = 0; j < M + N; j++)
                {
                    if (mp.find(A[i][j]) == mp.end())
                    {
                        auto itPair = equal_range(input[i], input[i] + M + N, A[i][j]);
                        mp[A[i][j]] = distance(itPair.first, itPair.second);
                    }

                    //storing ranks of the original array
                    A[i][j] = (lower_bound(input[i], input[i] + M + N, A[i][j]) - input[i]) + mp[A[i][j]]--;
                    cout << A[i][j] << ' ';
                }
                cout << endl;
            }
            //pair LIS
            B = vector<tuple<int, int, int>>();
            seg = segtree(M + N + 1);
            for (int i = 0; i < M + N; i++)
            {
                B.push_back(make_tuple(A[0][i], A[1][i], A[2][i]));
            }
            sort(B.begin(), B.end());
            memset(dp, 0, sizeof(dp));

            ans = sol(0, M + N - 1);
        }
        cout << ans << '\n';
    }
}