#include <bits/stdc++.h>
using namespace std;
int N;
int arr[33][33];
int eval(){
    int ret = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            ret+=arr[i][j];
        }
    }
    return ret;
}

void turn(int x, bool col){
    if(!col){
        for(int i = 0; i < N; i++){
            arr[x][i]=1-arr[x][i];
        }
    } else {
        for(int i = 0; i < N; i++){
            arr[i][x]=1-arr[i][x];
        }
    }
}
/*
T: temperature
D: temperature decreasing factor = entropy decreases faster (normally 0.9995~0.9999)
K: boltzmann coefficient, bigger = greater entropy
LIM: limit temperature
*/
double T = 1, D = 0.9999, K = 25, LIM = 0.0003;

int simulated_annealing(){
    random_device rd;
    mt19937_64 seed(rd());
    mt19937 poseed(rd());
    uniform_real_distribution<double> rng(0,1);
    uniform_int_distribution<int> posrng(0,N-1);
    int ret = 999;
    double e1,e2;
    vector<vector<int>> ori(33,vector<int>(33));
    while(T>LIM){
        e1=eval();
        //change state
        for(int i = 0; i < N; i++)for(int j = 0; j < N; j++)ori[i][j]=arr[i][j];

        int pos = posrng(poseed);
        int qual = rand()%2;
        turn(pos,qual);
        e2=eval();

        double p = exp((e1-e2)/(K*T));
        if(p<rng(seed)){
            //return to original state
            for(int i = 0; i < N; i++)for(int j =0; j < N; j++)arr[i][j]=ori[i][j];
        }
        T*=D;

        ret = min(ret,eval());
    }
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            char c;
            cin>>c;
            arr[i][j]=(int)(c=='T');
        }
    }
    cout << simulated_annealing();
}