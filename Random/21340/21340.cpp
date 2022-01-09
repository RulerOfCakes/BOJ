#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi=pair<ll,ll>;
int N;
int dx[]={1,1,-1,-1};
int dy[]={1,-1,1,-1};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(0,1e6);
    auto gen = bind(distribution,rng);
    cin >> N;
    //find n balls
    while(N--){
        ll px=gen(), py=gen();
        cout << px << ' ' << py << endl;
        ll res;
        cin>>res;
        if(!res){
           continue;
        }
        ll x=sqrt(res)+1;
        vector<pi> pts;
        for(ll y = 0; y*y<=res; y++){
            while(y*y+x*x>res&&x>=0)x--;
            if(x*x+y*y!=res)continue;
            else{
                pts.push_back({x,y});
            }
        }
        ll tmp=-1;
        for(pi pt : pts){
            for(int i = 0; i < 4; i++){
                ll nx = px+pt.first*dx[i],ny=py+pt.second*dy[i];
                if(nx<0||nx>1e6||ny<0||ny>1e6)continue;
                cout << nx << ' ' << ny << endl;
                cin>>tmp;
                if(!tmp)break;
            }
            if(!tmp)break;
        }
    }
}