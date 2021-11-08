#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int N;
int arr[65][65];
int psum[65][65];
string sol(int sx, int sy,int ex, int ey){
    string ret = "";
    if(sx==ex&&sy==ey){
        return to_string(arr[sx][sy]);
    }
    int csum=psum[ex][ey]-psum[sx-1][ey]-psum[ex][sy-1]+psum[sx-1][sy-1];
    if(csum==0){
        ret.push_back('0');
    }
    else if(csum==(ex-sx+1)*(ey-sy+1)){
        ret.push_back('1');
    }
    else{
        ret.push_back('(');
        int mx=sx+ex>>1,my=sy+ey>>1;
        ret+=sol(sx,sy,mx,my);
        ret+=sol(sx,my+1,mx,ey);
        ret+=sol(mx+1,sy,ex,my);
        ret+=sol(mx+1,my+1,ex,ey);
        ret.push_back(')');
    }

    return ret;
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    for(int i = 1; i <= N; i++){
        string s;
        cin >> s;
        for(int j = 1; j <= N; j++){
            arr[i][j]=s[j-1]-'0';
            psum[i][j]=psum[i][j-1]+psum[i-1][j]-psum[i-1][j-1]+arr[i][j];
        }
    }
    cout << sol(1,1,N,N);
}