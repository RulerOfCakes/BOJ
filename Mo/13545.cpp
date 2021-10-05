#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int,int>;
using ppi = pair<pi,pi>;
using pii = pair<pi, int>;

int T,N,K,M,sz;
const int INF = 1e9;
vector<int> arr;

int cnt[201012];
//list is faster than deque
list<int> idxs[201012];
int ans[201012];
vector<int> bucket;

void add(int i, bool dir){
    int cval=0;
    auto& dq = idxs[arr[i]];
    if(!dq.empty()){
        cval = dq.back()-dq.front();
        cnt[cval]--;
        bucket[cval/sz]--;
    }
    if(!dir)dq.push_front(i);
    else dq.push_back(i);
    cval = dq.back() - dq.front();
    cnt[cval]++; bucket[cval/sz]++;
}
void erase(int i, bool dir){
    auto& dq = idxs[arr[i]];
    int cval = dq.back()-dq.front();
    cnt[cval]--;bucket[cval/sz]--;
    if(!dir)dq.pop_front();
    else dq.pop_back();
    if(!dq.empty()){
        cval=dq.back()-dq.front();
        cnt[cval]++;bucket[cval/sz]++;
    }
}

int query(){
    for(int i = bucket.size()-1; i >= 0; i--){
        if(bucket[i]==0)continue;
        for(int j = sz-1; j >= 0; j--){
            if(cnt[i*sz+j]>0)return i*sz+j;
        }
    }
    return 0;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    sz = sqrt(N);
    arr=vector<int>(N+1);
    bucket=vector<int>(sz+2);
    arr[0]=100001;
    for(int i = 1; i <= N; i++){
        int a;
        cin >> a;
        arr[i]=arr[i-1]+a;
    }
    cin >> M;
    vector<pii> queries(M);
    for(int i = 0; i < M; i++){
        int a,b;
        cin >> a >> b;
        queries[i]={{a-1,b},i};
    }
    sort(queries.begin(),queries.end(),[&](pii p1, pii p2){
        if(p1.first.first/sz != p2.first.first/sz)return p1.first.first<p2.first.first;
        return p1.first.second<p2.first.second;
    });
    int l = queries[0].first.first, r = queries[0].first.second;
    for(int i = l; i <= r; i++){
        add(i,1);
    }
    ans[queries[0].second]=query();
    
    for(int i = 1; i < M; i++){
        while(queries[i].first.first<l)add(--l,0);
        while(r<queries[i].first.second)add(++r,1);
        while(l<queries[i].first.first)erase(l++,0);
        while(queries[i].first.second<r)erase(r--,1);
        ans[queries[i].second]=query();
    }
    for(int i = 0; i < M; i++){
        cout << ans[i] << '\n';
    }
}