#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int,int>;

int N, A, B;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while (true)
    {
        cin >> N >> A >> B;
        if (!N && !A && !B)
            return 0;
        vector<pair<pi,int>> v;
        for(int i = 0; i < N; i++){
            int a,b,c;
            cin >> c>> a >> b;
            v.push_back({{a,b},c});
        }  
        sort(v.begin(),v.end(),[&](pair<pi,int>& p1, pair<pi,int>& p2){
            return abs((p1.first.first-p1.first.second))>abs((p2.first.first-p2.first.second));
        });
        int ans = 0;
        for(int i = 0; i < v.size(); i++){
            int adist=v[i].first.first,bdist=v[i].first.second,bloons=v[i].second;
            if(adist<bdist){
                if(A<bloons){
                    ans+=adist*A;
                    ans+=bdist*(bloons-A);
                    A=0;
                }
                else{
                    A-=bloons;
                    ans+=adist*bloons;
                }
            }
            else{
                if(B<bloons){
                    ans+=bdist*B;
                    ans+=adist*(bloons-B);
                    B=0;
                }
                else{
                    B-=bloons;
                    ans+=bdist*bloons;
                }

            }
        }
        cout << ans << '\n';
    }
}