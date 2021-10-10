#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;

int N, M, startp, endp;

int idx[400003];
vector<int> edges[400003];
map<string,int> mp;
map<int,string> rmp;


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    string as,bs;
    int cidx=1;
    vector<pair<string,string>> qv;
    
    unordered_set<string> st;
    for(int i = 0; i < N; i++){
        cin >> as >> bs;
        qv.push_back({as,bs});
        st.insert(as);
        st.insert(bs);
    }
    vector<string> sv(st.begin(),st.end());
    sort(sv.begin(),sv.end());
    for(string s : sv){
        mp[s]=cidx;
        rmp[cidx]=s;
        cidx++;
    }
    
    for(int i = 0; i < N; i++){
        tie(as,bs) = qv[i];
        int i1 = mp[as],i2=mp[bs];
        edges[i1].push_back(i2);
        idx[i2]++;
    }

    deque<int> dq;
    for(int i = 1; i <= cidx-1; i++){
        if(!idx[i]){
            dq.push_back(i);
        }
    }
    vector<int> ans;
    while(!dq.empty()){
        sort(dq.begin(),dq.end());
        deque<int> newq;
        while(!dq.empty()){

            int curp = dq.front();
            ans.push_back(curp);
            dq.pop_front();

            for(auto i : edges[curp]){
                int next = i;
                
                if(!--idx[next]){
                    newq.push_back(next);
                }
                
            }
        }
        if(newq.empty())break;
        dq=newq;
    }
    if(ans.size()<cidx-1){
        cout << -1;
        return 0;
    }
    for(int i : ans){
        cout << rmp[i] << '\n';
    }
}