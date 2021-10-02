#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int,int>;
using ppi = pair<pi,int>;

int T,N,M;
const int INF = 1e9;
int cnt[1000002];
int ans[1000002];
int cur;

void add(int i){
    //new number = increased answer
    if(++cnt[i]==1)cur++;
}
void erase(int i){
    //number gone = decreased answer
    if(--cnt[i]==0)cur--;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    int sz = sqrt(N);
    vector<int> arr(N);
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    cin >> M;
    vector<pair<pi,int>> queries(M);
    for(int i = 0; i < M; i++){
        int a,b;
        cin >> a >> b;
        queries[i]={{a-1,b-1},i};
    }
    sort(queries.begin(),queries.end(),[&](ppi p1, ppi p2){
        if(p1.first.second/sz==p2.first.second/sz){
            return p1.first.first<p2.first.first;
        }
        return p1.first.second/sz<p2.first.second/sz;
    });
    int l = 0,r=0;
    add(arr[0]);
    for(int i = 0; i < M; i++){
        int nl = queries[i].first.first,nr=queries[i].first.second;
        //erasing previous query exclusives
        for(int j = l; j < nl; j++){
            erase(arr[j]);
        }
        //if l > nr
        for(int j = l-1; j >= nl; j--){
            add(arr[j]);
        }
        //if r < nr
        for(int j = r+1; j <= nr; j++){
            add(arr[j]);
        }
        //removing current query exclusives
        for(int j = r; j > nr; j--){
            erase(arr[j]);
        }
        l=nl;
        r=nr;
        ans[queries[i].second]=cur;
    }
    for(int i = 0; i < M; i++){
        cout << ans[i] << '\n';
    }
}