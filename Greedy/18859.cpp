#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N,M;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;vector<int>v(N);
    map<int,int> mp;
    for(int i = 0; i < N; i++){
        cin>>v[i];
        mp[v[i]]++;
    }
    sort(v.begin(),v.end());
    int midpoint = v[0];
    string ans = "Yes";
    int def = v[1]-v[0];
    if(!def){
        cout<<"No";
        return 0;
    }
    int cnt=1,cx=v[0];
    while(mp[cx+def]){
        cnt++;
        mp[cx+def]--;cx=cx+def;
    }
    int px=-1;
    if(cnt>1){
        px=cx;
        mp[cx]++;
    }
    int token=0;
    if(cnt<N){
        bool found=0;
        for(int i = 1; i < N; i++){
            if(mp[v[i]]){
                cx=v[0];
                found=1;
                def=v[i]-v[0];
                break;
            }
        }
        if(found){
            while(mp[cx+def]){
                cnt++;
                if(cx+def==px&&mp[cx+def]==1){
                    token=1;
                }
                mp[cx+def]--;cx=cx+def;
            }
        }
    }
    //cout << cnt << '\n';
    cout << (cnt-token==N?"Yes":"No");
}