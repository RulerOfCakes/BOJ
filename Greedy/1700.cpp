#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
vector<int> prio,sch;

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    int N,K;cin>>N>>K;
    prio=vector<int>(K+1);
    sch=vector<int>(K);
    for(int i =0; i < K; i++){
        int x;cin>>x;
        prio[x]++;
        sch[i]=x;
    }
    vector<int> tabs;
    map<int,bool> mp;
    int cnt=0;
    for(int i = 0; i < K; i++){
        int nx=sch[i];
        prio[nx]--;
        if(mp[nx])
            continue;
        if(tabs.size()<N){
            tabs.push_back(nx);
            mp[nx]=1;
        }
        else{
            bool done=0;
            vector<int>::iterator titer=tabs.begin();
            int tidx=0;
            for(auto iter=tabs.begin();iter!=tabs.end();iter++){
                if(!prio[*iter]){
                    done=1;
                    mp[*iter]=0;
                    tabs.erase(iter);
                    break;
                } else {
                    for(int j = i; j < K; j++){
                        if(sch[j]==*iter){
                            if(j>tidx){
                                tidx=j;
                                titer=iter;
                            }
                            break;
                        }
                    }
                }
            }
            if(!done){
                mp[*titer]=0;
                tabs.erase(titer);
            }
            tabs.push_back(nx);
            mp[nx]=1;
            cnt++;
            //cout << cnt << ' ' << nx << '\n';
        }
            //cout << nx << ' ' << mp[nx] << '\n';
    }
    cout << cnt;
}