#include <bits/stdc++.h>

using namespace std;
int N, K;
string s1, s2;
int pi[402];
int cnt;
void getPi(){
    int n = s2.length();
    for(int i = 1, mat=  0; i < n; ++i){
        if(s2[i] == s2[mat]){
            pi[i] = ++mat;
        } else if(mat != 0){
            --i;
            mat = pi[mat-1];
        }
    }
}
int res[402];
void kmp(){
    int n = s1.length(), m = s2.length();
    //i: index, mat: number of matches
    for(int i = 0, mat = 0; i < n; i++){
        if(s1[i]==s2[mat]){
            if(++mat==m){
                res[cnt++] = i-m+1;
                mat=pi[mat-1];
            }
        }
        else if (mat != 0){
            --i;
            mat = pi[mat-1];
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin>>N;vector<string>v(N);
    vector<int> idxs(N);

    for(int i = 0; i < N; i++){
        cin>>v[i];
        idxs[i]=i;
    }
    cin>>K;
    int ans =0;
    do{
        memset(pi,0,sizeof(pi));
        memset(res,0,sizeof(res));
        cnt=0;
        s2="";
        for(int i = 0; i < N; i++){
            s2+=v[idxs[i]];
        }
        s1=s2+s2;
        s1.pop_back();
        getPi();
        kmp();
        if(cnt==K)ans++;
    }while(next_permutation(idxs.begin(),idxs.end()));
    cout << ans;
}