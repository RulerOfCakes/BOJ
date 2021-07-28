#include <bits/stdc++.h>

using namespace std;
int N;
int arr[48][48][48];


//up -> right -x, left -y
//down -> right +x, left +y

//prev 123 456

int sol(int n, int x, int y, int z, int prev){
    if(n==0){
        if(arr[x][y][z])return 1;
        else return 0;
    }
    if(arr[x][y][z])return 0;
    int ret=0;
    arr[x][y][z]=1;
    if(prev==0){
        ret+=sol(n-1,x,y-1,z,4);
        ret+=sol(n-1,x,y,z-1,5);
    }
    else if(prev==1){
        ret+=sol(n-1,x-1,y,z,3);
        ret+=sol(n-1,x,y,z-1,5);
    }
    else if(prev==2){
        ret+=sol(n-1,x-1,y,z,3);
        ret+=sol(n-1,x,y-1,z,4);
    }
    else if(prev==3){
        ret+=sol(n-1,x,y+1,z,1);
        ret+=sol(n-1,x,y,z+1,2);
    }
    else if(prev==4){
        ret+=sol(n-1,x+1,y,z,0);
        ret+=sol(n-1,x,y,z+1,2);
    }
    else if(prev==5){
        ret+=sol(n-1,x+1,y,z,0);
        ret+=sol(n-1,x,y+1,z,1);
    }
    arr[x][y][z]=0;
    return ret;
}


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    arr[24][24][23]=1;
    cout << sol(N,24,24,24,2);
}