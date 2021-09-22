#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N, M;
const ll INF = 1e15;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    vector<int>nv,pv;
    int maxn = 0;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        if(abs(a)>maxn)maxn=abs(a);
        if(a>0)pv.push_back(a);
        else nv.push_back(-a);
    }
    sort(pv.begin(),pv.end(),greater<int>());
    sort(nv.begin(),nv.end(),greater<int>());
    int ans = 0,i=0;
    int pN = pv.size(), nN = nv.size();
    for(i = 0; i < pN; i+=M){
        ans+=pv[i]*2;
    }
    
    for(i = 0; i < nN; i+=M){
        ans+=nv[i]*2;
    }
    
    cout << ans-maxn;
}