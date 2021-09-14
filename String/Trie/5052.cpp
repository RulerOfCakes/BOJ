#include <bits/stdc++.h>

using namespace std;
int T, N;
const int LENGTH = 11;

int char_to_idx(char c){
    return c-'0';
}

struct Trie{
    bool is_end;
    bool nextChild;
    Trie* children[LENGTH];
    Trie():is_end(false){
        memset(children,0,sizeof(children));
    }

    ~Trie(){
        for(int i = 0; i < LENGTH; i++){
            if(children[i])delete children[i];
        }
    }

    bool insert(const char* key){
        if(*key == '\0'){
            is_end=true;
            if(nextChild)return 0;
            else return 1;
        }

        
        int idx = char_to_idx(*key);

        if(!children[idx]){
            children[idx]=new Trie();
        }
        nextChild=true;
        bool ret = children[idx]->insert(key+1);
        
        return !is_end&&ret;
    }
};
char arr[10002][11];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--){
        cin >> N;
        cin.clear();
        for(int i = 0 ;i  < N; i++){
            cin >> arr[i];
        }
        Trie* tr = new Trie;
        bool ans = 1;
        for(int i = 0; i < N; i++){
            if(!(tr->insert(arr[i])))ans=0;
        }

        if(ans){
            cout << "YES\n";
        }
        else cout << "NO\n";
    }
}