#include <bits/stdc++.h>
using namespace std;
int N, M;
int sol(const vector<int>& v, int grp){
    int ret=0,cnt=0;
    vector<int> visited(500002);
    int l = 0, r = 0;
    while(r<N){
        if(visited[v[r]]){
            while(l<r){
                visited[v[l]]=0;
                if(v[l++]==v[r])break;
            }
        }

        if(r-l+1==grp){
            ret+=grp;cnt++;
            while(l<=r){
                visited[v[l++]]=0;
            }
            r++;
            continue;
        }
        else
            visited[v[r++]]=1;
        
    }

    return (cnt>=M?ret:-1);
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M;
    vector<int>v(N);
    for(int i = 0; i < N; i++){
        cin>>v[i];
    }
    int l = 1, r = N;
    int ans = 1;
    while(l<=r){
        int mid = l+r>>1;
        int res = sol(v,mid);
        if(res==-1){
            r=mid-1;
        } else {
            l=mid+1;
            ans=max(ans,mid);
            //cout << "HA" << endl;
        }
    }
    cout<<ans;
}