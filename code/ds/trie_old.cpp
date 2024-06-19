struct Trie {

    int nxt = 1, sz, maxLet = 26; //tamanho do alfabeto
    vector< vector<int> > trie;
    bitset<(int)1e7> finish; //modificar esse valor pra ser >= n
    //garantir que vai submeter em cpp 64

    Trie(int n){
        sz = n;
        trie.assign(sz, vector<int>(maxLet,0));
    }

    void add(string &s){
        int cur = 0;
        for(auto c: s){
            //alterar esse azinho dependendo da entrada!!
            if(trie[cur][c-'a'] == 0){
                trie[cur][c-'a'] = nxt++;
                cur = trie[cur][c-'a'];
            } else {
                cur = trie[cur][c-'a'];
            }
        }
        finish[cur] = 1;
    }

    int search(string& s){
        int cur = 0;
        for(auto c: s){
            if(trie[cur][c - 'a'] == 0){
                return 0;
            }
            cur = trie[cur][c-'a'];
        }
        return finish[cur];
    }

};