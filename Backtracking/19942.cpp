#include <bits/stdc++.h>

using namespace std;

int N;
int mp,mf,ms,mv;
const int INF = 1e9;
int p[16],f[16],s[16],v[16];
int cost[16];

pair<int,vector<int>> sol(int cx, int cp, int cf, int cs, int cv){
    if(cp>=mp&&cf>=mf&&cs>=ms&&cv>=mv)return {0,vector<int>()};
    if(cx>=N){
        if(cp<mp||cf<mf||cs<ms||cv<mv)return {INF,vector<int>()};
        else return {0,vector<int>()};
    }
    int ret; vector<int>retv;
    tie(ret,retv)=sol(cx+1,cp+p[cx],cf+f[cx],cs+s[cx],cv+v[cx]);
    ret+=cost[cx];
    retv.push_back(cx+1);
    int sret;vector<int>sretv;
    tie(sret,sretv)= sol(cx+1,cp,cf,cs,cv);
    if(ret>sret){

        return {sret,sretv};
    }
    else if (ret<sret){

        return {ret,retv};
    }
    else{
        if(ret>=INF){
            return {INF,vector<int>()};
        }
        if(sretv.empty()||retv.back()>sretv.back()){
            return {sret,sretv};
        }
        else return {ret,retv};
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    cin >> mp >> mf >> ms >> mv;
    for(int i = 0; i < N; i++){
        cin >> p[i] >> f[i] >> s[i] >> v[i] >> cost[i];
    }
    int ans;vector<int>v;
    tie(ans,v)=sol(0,0,0,0,0);
    if(ans>=INF){
        cout << -1 << '\n';
        return 0;
    }
    cout << ans << '\n';
    for(int i = v.size()-1; i >= 0; i--){
        cout << v[i] << ' ';
    }
}