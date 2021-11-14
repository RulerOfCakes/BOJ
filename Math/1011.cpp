#include <bits/stdc++.h>
using namespace std;
int T;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--)
    {
        int x, y;
        cin >> x >> y;
        int dist=abs(x-y);
        int n = sqrt(dist), left=dist-n*n;
        cout << 2*n-1+left/n+(left%n>0?1:0) << '\n';
    }
}