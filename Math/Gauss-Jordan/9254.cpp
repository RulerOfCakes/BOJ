#include <bits/stdc++.h>
using namespace std;
int N,M;
template <typename T>
class GaussJordan{
public:
    int N,M;
    vector<vector<T>> mtx;
    GaussJordan(const vector<vector<T>>& mtx):mtx(mtx),N(mtx.size()),M(mtx[0].size()){}
    bool RREF(){
        bool flag=0;
        for(int i = 0; i < N; i++){
            if(mtx[i][i]==0){
                //look for swaps in other rows
                int c=1;
                while((i+c)<N&&mtx[i+c][i]==0)c++;
                if((i+c)==N){
                    //no available rows, impossible to continue
                    flag=1;break;
                }
                //initiate swap
                mtx[i].swap(mtx[i+c]);
            }
            //continue conversion to RREF
            for(int j = 0; j < N; j++){
                if(i==j)continue;
                T eff = mtx[j][i]/mtx[i][i];
                for(int k = 0; k <= N; k++){
                    mtx[j][k]-=eff*mtx[i][k];
                }
            }
        }
        return flag;
    }
    bool inverse(vector<vector<T>>& out){
        bool flag=0;
        for(int i = 0; i < N; i++){
            if(!mtx[i][i]){
                //look for swaps in other rows
                int c=1;
                while((i+c)<N&&!mtx[i+c][i])c++;
                if((i+c)==N){
                    //no available rows, impossible to continue
                    flag=1;break;
                }
                //initiate swap
                mtx[i].swap(mtx[i+c]);
                out[i].swap(out[i+c]);
            }
            //continue conversion to identity matrix
            T d = mtx[i][i];
            for(int j = 0; j < N; j++){
                mtx[i][j]/=d;out[i][j]/=d;
            }
            for(int j = 0; j < N; j++){
                if(i==j)continue;
                T eff = mtx[j][i];
                for(int k = 0; k < N; k++){
                    mtx[j][k]-=eff*mtx[i][k];
                    out[j][k]-=eff*out[i][k];
                }
            }
            
        }
        return flag;
    }
    bool validity(){
        //0 for infinite solutions
        //1 for no solutions
        bool flag = 1;
        for(int i = 0; i < N; i++){
            T sum=0;
            for(int j = 0; j < N; j++){
                sum+=mtx[i][j];
            }
            if(sum==mtx[i][N]){
                flag=0;
            }
        }
        return flag;
    }
};
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    vector<vector<double>> mtx;
    for(int i = 0; i < N; i++){
        int a;
        vector<double> v;
        for(int i = 0; i < N; i++){
            cin>>a;
            v.push_back(a);
        }
        mtx.push_back(v);
    }
    GaussJordan<double> gj(mtx);
    vector<vector<double>> out(N,vector<double>(N,0));
    for(int i = 0; i < N; i++)out[i][i]=1;
    if(gj.inverse(out))cout << "no inverse";
    else{
        cout.precision(8);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cout << out[i][j] << ' ';
            }
            cout << '\n';
        }
    }
}