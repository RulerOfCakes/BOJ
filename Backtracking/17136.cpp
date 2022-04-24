#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int N,M;
const int INF = 1e9;
vector<vector<int>>v(10,vector<int>(10));
int used[6];
pi boardcheck(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(v[i][j]==1)return {i,j};
        }
    }
    return {-1,-1};
}
bool flipper(int x, int y, int num){
    if(x+num>10||y+num>10)return false;
    for(int i = x; i < x+num; i++){
        for(int j = y; j < y+num; j++){
            if(v[i][j]==0)return false;
        }
    }
    for(int i = x; i < x+num; i++){
        for(int j = y; j < y+num; j++){
            v[i][j]=0;
        }
    }
    return true;
}
void unflip(int x, int y, int num){
    for(int i = x; i < x+num; i++){
        for(int j = y; j < y+num; j++){
            v[i][j]=1;
        }
    }
}
int sol(){
    int ret = INF;
    bool done=1;
    for(int i = 1; i <= 5; i++){
        if(used[i])done=0;
    }
    pi nxt = boardcheck();
    if(nxt==make_pair(-1,-1))return 0;
    if(done)return ret;
    for(int i = 5; i >=1; i--){
        if(!used[i])continue;
        if(flipper(nxt.first,nxt.second,i))used[i]--;
        else continue;
        int tmp = sol();
        ret=min(ret,tmp+1);
        used[i]++;
        unflip(nxt.first,nxt.second,i);
    }
    return ret;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    for(int i = 1; i <= 5; i++)used[i]=5;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cin>>v[i][j];
        }
    }
    int result = sol();
    cout << (result>=INF?-1:result);
}