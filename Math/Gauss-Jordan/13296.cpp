#include <bits/stdc++.h>
using namespace std;

vector<int> gauss_mod(vector<vector<int>> &a,int mod){
    vector<int> inv(mod); // modulo inverse 
    inv[1] = 1;
    for(int i = 2; i < mod; ++i)
        inv[i] = mod - (mod/i) * inv[mod%i] % mod;

    int n = a.size();
    int m = a[0].size();

    vector<int> w(m, -1); // i번째 열에 있는 pivot이 몇 번째 행에 있는지 저장
    for(int c = 0, r = 0; c < m && r < n; ++c){
        int p = r; // pivot row
        for(int i = r; i < n; ++i)
            if(a[p][c] < a[i][c])
                p = i;
        if(a[p][c] == 0) continue; // free variable - 0
        
        a[p].swap(a[r]);
        
        w[c] = r;

        int t = a[r][c];
        for(int j = 0; j < m; ++j)
            a[r][j] = a[r][j] * inv[t] % mod;

        for(int i = 0; i < n; ++i) if(i != r){
            int t = a[i][c];
            for(int j = c; j < m; ++j)
                a[i][j] = (a[i][j] - a[r][j] * t % mod + mod) % mod;
        }
        ++r;
    }

    for(int i = 0; i < n; ++i) // existence of solution
        if(count(a[i].begin(), --a[i].end(), 0) == m-1 && a[i][m-1])
            return vector<int>(); // no solution

    vector<int> ans(m);
    for(int i = 0; i < m; ++i)
        if(~w[i]) ans[i] = a[w[i]][m-1];
    return ans; // solution exist
}
int N,M,P;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M>>P;
    vector<vector<int>> v(N,vector<int>(M));
    for(int i = 0; i < N; i++)for(int j = 0; j < M; j++)cin>>v[i][j];
    vector<vector<int>> rv(N*M,vector<int>(N*M+1));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            int cx=i*M+j;
            for(int k = 0; k < N; k++){
                rv[cx][k*M+j]=1;
            }
            for(int k = 0; k < M; k++){
                rv[cx][i*M+k]=1;
            }
            rv[cx][N*M]=(P-v[i][j])%P;
        }
    }
    auto ans = gauss_mod(rv,P);
    if(ans.empty()){
        cout << -1 << '\n';return 0;
    }
    vector<int> out;
    for(int i = 0; i < ans.size(); i++){
        while(ans[i]--)
            out.push_back(i+1);
    }
    cout << out.size() << '\n';
    for(int x : out)cout << x << ' ';
}