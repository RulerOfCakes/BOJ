#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi=pair<int,int>;
using ppi = pair<pi,pi>;
int N;
int ttime[402];
int spend[402][3];
bool mp[3][3][402][402];
ll arr[2][402],lea[2][402];
int inc(int x){
    return (x+1)%N;
}
int dec(int x){
    return (x+N-1)%N;
}
bool run_sim(int p, int q, int x, int y){
    arr[0][x]=0;lea[0][x]=spend[x][p];
    for(int i = (x+1)%N; i !=x; i=inc(i)){
        arr[0][i]=lea[0][dec(i)]+ttime[dec(i)];
        lea[0][i]=arr[0][i]+spend[i][p];
    }
    arr[1][y]=0;lea[1][y]=spend[y][q];
    if(arr[1][y]<lea[0][y]&&arr[1][y]>=arr[0][y])return false;
    if(arr[0][y]<lea[1][y]&&arr[0][y]>=arr[1][y])return false;

    for(int i = (y+1)%N; i !=y; i=inc(i)){
        arr[1][i]=lea[1][dec(i)]+ttime[dec(i)];
        lea[1][i]=arr[1][i]+spend[i][q];
        if(arr[1][i]<lea[0][i]&&arr[1][i]>=arr[0][i])return false;
        if(arr[0][i]<lea[1][i]&&arr[0][i]>=arr[1][i])return false;
    }

    return true;
}

// bool runsim(int p, int q, int x, int y){
//     vector<vector<bool>> vis(N+2,vector<bool>(2));
//     int cx=x,cy=y;
//     int xtime=0,ytime=0;
//     do{
//         if(xtime<ytime){
//             if(inc(cx)==x)return true;
            
//             int nxtime=xtime+spend[cx][p]+ttime[cx];
//             int cytime=ytime+spend[cy][q];
//             if((inc(cx)==cy)&&(nxtime<cytime&&nxtime>=ytime))return false;
            
//             xtime=nxtime;
//             cx=inc(cx);
//             vis[cx][0]=1;
//         }
//         else{
//             if(inc(cy)==y)return true;
//             int nytime=ytime+spend[cy][q]+ttime[cy];
//             int cxtime=xtime+spend[cx][p];
//             if((inc(cy)==cx)&&(nytime<cxtime&&nytime>=xtime))return false;
//             ytime=nytime;
//             cy=inc(cy);
//             vis[cy][1]=1;
//         }
//         //cout << cx << ' ' << cy << ' ' << xtime << ' ' << ytime << endl;
//     }
//     while(!vis[x][0]&&!vis[y][1]);
//     return true;
// }

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>N;
    for(int i = 0; i < N; i++)
        cin>>ttime[i];
    
    for(int j = 0; j < 3; j++)
        for(int i = 0; i < N; i++)
            cin>>spend[i][j];
      
    for(int p = 0; p < 3; p++){
        for(int q = p+1; q < 3; q++){
            for(int i = 0; i < N; i++){
                for(int j = inc(i); j != i; j=inc(j)){
                    mp[p][q][i][j]=run_sim(p,q,i,j);
                    mp[q][p][j][i]=mp[p][q][i][j];
                }
            }
        }
    }
    //cout << "HAAH"<<endl;
    bool found=0;
    for(int i = 0; i < N; i++){
        if(found)break;
        for(int j = inc(i); j !=i; j=inc(j)){
            if(found)break;
            for(int k = inc(j); k !=j; k=inc(k)){
                if(found)break;
                if(k==i)continue;
                if(mp[0][1][i][j]&&mp[1][2][j][k]&&mp[0][2][i][k]){
                    found=1;
                    cout << i+1 << ' ' << j+1 << ' ' << k+1;
                }
            }
        }
    }
    if(!found){
        cout<<"impossible";
    }
}