#include <bits/stdc++.h>
using namespace std;
string s1,s2;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> s1 >> s2;
    stack<char> s;
    for(char c : s1){
        s.push(c);
        if(c==s2.back()&&s.size()>=s2.size()){
            string tmp;
            for(int j = 0; j < s2.size(); j++){
                tmp.push_back(s.top());s.pop();
            }
            reverse(tmp.begin(),tmp.end());
            bool cope=1;
            for(int j = 0; j < tmp.size(); j++){
                if(tmp[j]!=s2[j]){
                    cope=0;
                    break;
                }
            }
            if(!cope)for(int j = 0; j < tmp.size(); j++){
                s.push(tmp[j]);
            }
        }
    }
    if(s.empty()){
        cout << "FRULA";
    }
    else{
        string ans;
        while(s.size()){
            ans.push_back(s.top());
            s.pop();
        }
        reverse(ans.begin(),ans.end());
        cout << ans;
    }
}