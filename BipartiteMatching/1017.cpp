#include <bits/stdc++.h>

using namespace std;

int N, M;
//const int INF = 1e9;
vector<bool> visited;
vector<int> match1,match2;
vector<vector<int>> v;
vector<bool> primes(2005);
map<pair<int,int>,bool> mp;
bool dfs(int x){
    if(visited[x])return false;
    visited[x]=1;

    for(int i = 0; i < v[x].size(); i++){
        int next = v[x][i];
        if(mp.count({x,next})||mp.count({next,x}))continue;
        if(match2[next]==-1 || dfs(match2[next])){
                match1[x]=next;
                match2[next]=x;
                return true;
        }
    }
    return false; 
}

int main(){
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    primes[0]=primes[1]=1;
    for(int i = 2; i <= 2000; i++){
        if(!primes[i]){
            for(int j = i*2; j <= 2000; j+=i)primes[j]=1;
        }
    }
    cin >> N;
    v = vector<vector<int>>(1001, vector<int>());
    visited = vector<bool>(1001 , 0);
    
    vector<int> iv;
    for(int i = 1; i <= N; i++){
        int a;
        cin >> a;
        iv.push_back(a);
    }
    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            if(!primes[iv[i]+iv[j]]){
                    v[i].push_back(j);
                    v[j].push_back(i);
                //cout << iv[i] << ' ' << iv[j] << '\n';
            }
        }
    }
    int cnt=0; 
    vector<int> ans;
    
    do{
        cnt=0;
        match1 = vector<int>(1001, -1);
        match2 = vector<int>(1001, -1);
        for(int i = 0; i < N; i++){
            if((iv[i]%2)!=(iv[0]%2))continue;
            fill(visited.begin(), visited.end(), 0);
            if(dfs(i))cnt++;
        }
        //cout << cnt << endl;
        if(cnt==N/2){
            int target=-1;
            for(int i = 0; i < N; i++){
                if(match2[i]==0){
                    target=i;
                    break;
                }
            }
            if(target==-1)break;
            ans.push_back(iv[target]);
            //cout << other << ' ' << iv[other] << '\n';
            
            mp[{0,target}]=1;
        }
    }while(cnt==N/2);
    
    if(ans.empty())cout << -1;
    else{
        sort(ans.begin(),ans.end());
        for(auto x : ans)cout << x << ' ';
    }
}