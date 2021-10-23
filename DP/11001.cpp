#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, D, maxi;
ll t[101010],v[101010], ans;
void DnCo(int s,int e,int is,int ie)
{
    if(s>e)return;
    int mid=(s+e)/2,id=0;
    ll maxi=0;
    for(int i=is;i<=ie;i++)
    {
        if(i-mid>D)continue;
        if( (i-mid)*t[i]+v[mid]>maxi )
        {
            maxi=(i-mid)*t[i]+v[mid];
            id=i;
        }
    }
    ans=max(ans,maxi);
    DnCo(s,mid-1,is,id);
    DnCo(mid+1,e,id,ie);
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> D;
    for(int i = 1; i <= N; i++){
        cin >> t[i];
    }
    for(int i = 1; i <= N; i++){
        cin >> v[i];
    }
    DnCo(1,N,1,N);
    cout << ans;
}