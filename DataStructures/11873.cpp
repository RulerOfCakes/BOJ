#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
int N, M;
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while(true){
        cin >> N >> M;
        if(N==0&&M==0)break;
        vector<int> hv(M+1);
        int ans=0;
        for(int i = 0; i < N; i++){
            stack<int> s;
            s.push(0);
            for(int j = 1; j <= M; j++){
                int a;
                cin>>a;
                if(!a)hv[j]=0;
                else hv[j]++;
                while(hv[s.top()]>hv[j]){
                    int cx=s.top();s.pop();
                    ans=max(ans,(j-s.top()-1)*hv[cx]);
                }
                s.push(j);
            }
            while(s.size()>1){
                int cx = s.top();s.pop();
                ans=max(ans,(M-s.top())*hv[cx]);
            }
        }
        cout << ans << '\n';
    }
    
}