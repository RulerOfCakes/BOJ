#include <bits/stdc++.h>

using namespace std;

int N, M;
int arr[100002];
bool bsearch(int start, int end, int val){
    if(start > end)return false;
    int mid = (start+end)/2;
    if(arr[mid] < val)
    return bsearch(mid+1, end, val);
    else if(arr[mid] > val)
    return bsearch(start, mid-1, val);
    else if(arr[mid] == val){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> arr[i];
    }
    sort(arr, arr+N+1);
    cin >> M;
    for(int i = 0; i < M; i++){
        int a;
        cin >> a;
        cout << bsearch(1, N, a) << '\n';
    }
}