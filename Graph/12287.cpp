#include <bits/stdc++.h>
using namespace std;
int N;
vector<vector<int>> adj(102, vector<int>()),badj(102,vector<int>());
vector<map<int,bool>> madj(102),mbadj(102);
list<int> ans;
bool visited[102];

void sol(list<int>::iterator liter){
    if(ans.size()==N)return;
    if(liter==ans.begin()){
        for(int nx : badj[*liter]){
            if(!visited[nx]){
                auto piter=ans.insert(liter,nx);
                visited[nx]=1;
                sol(piter);
                break;
            }
        }
    }
    if(ans.size()==N)return;
    liter++;
    auto niter = liter;
    liter--;
    if(niter==ans.end()){
        for(int nx : adj[*liter]){
            if(!visited[nx]){
                niter=ans.insert(niter,nx);
                visited[nx]=1;
                break;
            }
        }
    }
    if(ans.size()==N)return;
    if(niter==ans.end())return;
    for(int nx:adj[*liter]){
        if(!visited[nx]&&mbadj[*niter].count(nx)){
            niter=ans.insert(niter,nx);
            visited[nx]=1;
            sol(liter);
            break;
        }
    }
    if(ans.size()==N)return;
    liter++;
    if(liter==ans.end())return;
    sol(liter);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            char c;
            cin >> c;
            if(c=='+'){
                adj[i].push_back(j);
                madj[i][j]=1;
                badj[j].push_back(i);
                mbadj[j][i]=1;
            }
        }
    }
    visited[0]=1;
    ans.push_back(0);
    // auto iter = ans.begin();
    // while(iter!=ans.end()&&ans.size()<N){
    //     if(iter==ans.begin()){
    //         for(int nx : badj[*iter]){
    //             if(!visited[nx]){
    //                 iter=ans.insert(iter,nx);
    //                 visited[nx]=1;
    //                 break;
    //             }
    //         }
    //     } else {
    //         iter++;
    //         auto niter=iter;
    //         iter--;
    //         if(niter==ans.end()){
    //             for(int nx : adj[*iter]){
    //                 if(!visited[nx]){
    //                     ans.insert(niter,nx);
    //                     visited[nx]=1;
    //                     break;
    //                 }
    //             }
    //         }
    //         else{
    //             for(int nx: adj[*iter]){
    //                 if(!visited[nx]&&mbadj[*niter].count(nx)){
    //                     ans.insert(niter,nx);
    //                     visited[nx]=1;
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }
    sol(ans.begin());
    
    assert(ans.size()==N);
    
    for(int x : ans){
        cout << x << ' ';
    }
}