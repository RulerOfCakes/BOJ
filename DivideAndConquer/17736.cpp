#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;

int N;
string s;
map<int, map<int,int>> mp;
//j=o, o=i
//j-o=0, j-i=0

int sol(int l, int r){
    if(r-l<2)return 0;
    int ret = 0, mid = (l+r)/2;
    int tr = mid-1, tl = mid;
    int j = 0, o = 0, i = 0;
    while(l<=tr){
        if(s[tr]=='J')j++;
        else if(s[tr]=='O')o++;
        else if(s[tr]=='I')i++;
        mp[j-o][j-i]=tr--;
    }
    j=0;o=0;i=0;
    //need to keep count in inverse indices(mp[o-j][i-j])to match them
    while(tl<=r){
        if(s[tl]=='J')j++;
        else if(s[tl]=='O')o++;
        else if(s[tl]=='I')i++;
        if(mp[o-j].count(i-j))ret=max(ret,tl- mp[o-j][i-j]+1);
        tl++;
    }
    mp.clear();
    
    return max({ret,sol(l,mid-1),sol(mid+1,r)});
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> s;
    cout << sol(0,N-1);
}