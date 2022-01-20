#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<int> v,sv;

ll merge(int l, int r){
    int mid=l+r>>1;
    int i=l,j=mid+1,k=l;
    ll ret=0;
    while(i<=mid&&j<=r){
        if(v[i]<=v[j]){
            sv[k]=v[i];
            i++;
        }
        else{
            sv[k]=v[j];
            ret+=(j-k);
            j++;
        }
        k++;
    }
    while(j<=r){
        sv[k++]=v[j++];
    }
    while(i<=mid){
        sv[k++]=v[i++];
    }
    for(int n = l; n <= r; n++)v[n]=sv[n];
    return ret;
}

ll ms(int l, int r){
    if(l==r)return 0;
    int mid=l+r>>1;
    ll ret=0;
    ret+=ms(l,mid);
    ret+=ms(mid+1,r);
    ret+=merge(l,r);
    return ret;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin>>N;
    for(int i = 0; i < N; i++){
        int a;
        cin>>a;v.push_back(a);
        sv.push_back(a);
    }
    cout << ms(0,N-1);
}