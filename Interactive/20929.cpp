#include <bits/stdc++.h>
using namespace std;
int N;
void sol(int ax, int ay, int bx, int by)
{
    if (ax == ay && bx == by)
    {
        int a, b;
        cout << "? A " << ax << endl;

        cin >> a;
        cout << "? B " << bx << endl;
        cin >> b;
        cout << "! " << min(a, b) << endl;
        return;
    }
    int amid = ax + ay >> 1, bmid = bx + by >> 1;
    int aq, bq;
    cout << "? A " << amid << endl;
    cin >> aq;
    cout << "? B " << bmid << endl;
    cin >> bq;
    if (aq > bq)
    {
        sol(ax, amid, bmid + 1, by);
    }
    else if (bq > aq)
    {
        sol(amid + 1, ay, bx, bmid);
    }
    else
    {
        sol(ax, amid, bx, bmid);
    }
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    sol(1, N, 1, N);
}