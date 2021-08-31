#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<long long, long long>;

int T;
const int INF = 1e9 + 7;

int ccw(pi p1, pi p2)
{
    long long ret = p1.first * p2.second - p2.first * p1.second;
    if (ret < 0)
        return -1;
    else if (ret > 0)
        return 1;
    else
        return 0;
}

int ccw(pi p1, pi p2, pi p3)
{
    return ccw({p1.first - p3.first, p1.second - p3.second}, {p2.first - p3.first, p2.second - p3.second});
}

//checking for shared points/lines
bool chk(int st, int en, int d, int u)
{
    if (u > st && d < st)
        return true;
    if (u > en && d < en)
        return true;
    if (u <= en && d >= st)
        return true;
    if (u >= en && d <= st)
        return true;
    return false;
}

//checking for intersections(one exception(/-) is covered in diagonal())
bool intersect(pi p1, pi p2, pi p3, pi p4)
{
    if (ccw(p1, p2, p3) == ccw(p1, p2, p4))
        return false;
    if (ccw(p3, p4, p1) == ccw(p3, p4, p2))
        return false;
    return true;
}

//checking the exception from intersect
bool diagonal(pi p1, pi l1, pi l2)
{
    if ((l2.first - l1.first) * (p1.second - l1.second) == (l2.second - l1.second) * (p1.first - l1.first))
        return true;
    return false;
}
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    vector<pi> At, Bt;
    cin >> T;
    while (T--)
    {
        pi minp, maxp, p1, p2;
        cin >> minp.first >> minp.second >> maxp.first >> maxp.second;
        cin >> p1.first >> p1.second >> p2.first >> p2.second;
        if (p1.first == p2.first)
        {
            if (chk(minp.second, maxp.second, min(p1.second, p2.second), max(p1.second, p2.second)))
            {
                if (p1.first == minp.first || p1.first == maxp.first)
                {
                    cout << 4 << '\n';
                    continue;
                }
            }
            else if (minp.second == p1.second || minp.second == p2.second || maxp.second == p1.second || maxp.second == p2.second)
            {
                cout << 1 << '\n';
                continue;
            }
        }
        else if (p1.second == p2.second)
        {
            if (chk(minp.first, maxp.first, min(p1.first, p2.first), max(p1.first, p2.first)))
            {
                if (p1.second == minp.second || p1.second == maxp.second)
                {
                    cout << 4 << '\n';
                    continue;
                }
            }
            else if (minp.first == p1.first || maxp.first == p1.first || minp.first == p2.first || maxp.first == p2.first)
            {
                cout << 1 << '\n';
                continue;
            }
        }
        int cnt = 0;
        if (intersect(minp,{minp.first,maxp.second},p1,p2)){
            if(!diagonal(minp,p1,p2))cnt++;
        }
        if(intersect(minp,{maxp.first,minp.second},p1,p2)){
            if(!diagonal({maxp.first,minp.second},p1,p2))cnt++;
        }
        if(intersect({minp.first,maxp.second},maxp,p1,p2)){
            if(!diagonal({minp.first,maxp.second},p1,p2))cnt++;
        }
        if(intersect({maxp.first,minp.second},maxp,p1,p2)){
            if(!diagonal(maxp,p1,p2))cnt++;
        }

        cout << cnt << '\n';
    }
}