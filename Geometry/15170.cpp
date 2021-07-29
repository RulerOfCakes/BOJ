#include <bits/stdc++.h>

using namespace std;

using pd = pair<double, double>;
using Point = complex<double>;
struct Circle{ Point p; double r; };

Circle INVAL = Circle{Point(0,0), -1};
int N;
double arrx[102], arry[102];
char validity[102];
vector<Point> arr;
double pdist(double x, double y)
{
    return x * x + y * y;
}
Circle circle(Point a, Point b, Point c)
{
    b -= a;
    c -= a;
    double d = 2 * (conj(b) * c).imag();
    if (abs(d) < 1e-6)
        return INVAL;
    Point ans = (c * norm(b) - b * norm(c)) * Point(0, -1) / d;
    return Circle{a + ans, abs(ans)};
}
bool on(const Circle& c, Point p){ return abs(abs(c.p-p)-c.r)<1e-6; }
bool in(const Circle& c, Point p){ return abs(c.p-p) < c.r + 1e-6; }
bool allin(const Circle& c, const vector<Point>& v){
    for(auto p : v){
        if(on(c,p))continue;
        if(!in(c,p))return false;
    }
    return true;
}
bool allout(const Circle& c, const vector<Point>& v){
    for(auto p : v){
        if(on(c,p))continue;
        if(in(c,p))return false;
    }
    return true;
}
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    arr=vector<Point>(N);
    vector<Point> infected, ninfected;
    for (int i = 0; i < N; i++)
    {

        cin >> arrx[i] >> arry[i] >> validity[i];
        arr[i]=Point(arrx[i],arry[i]);
        if(validity[i]=='N')ninfected.push_back(arr[i]);
        else infected.push_back(arr[i]);
    }
    if(N<=2){
        cout << "No";
        return 0;
    }
    
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            
            Point center = Point((arrx[i]+arrx[j])/2,(arry[i]+arry[j])/2);
            
            Circle c = {center,abs(arr[i]-arr[j])/2};
            
            if(allin(c,infected)&&allout(c,ninfected)){
                cout << "No";
                return 0;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            for (int k = j + 1; k < N; k++)
            {
                
                Circle c = circle(arr[i],arr[j],arr[k]);
                //cout << c.p << ' ' << c.r << '\n';
                if(allin(c,infected)&&allout(c,ninfected)){
                cout << "No";
                return 0;
            }
            }
        }
    }
    cout << "Yes";
}