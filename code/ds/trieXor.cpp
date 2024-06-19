struct Trie {

    int nxt = 1, sz, maxLet = 2;
    vector< vector<int> > trie;
    vector<int> finish, paths;

    Trie(int n){
        sz = n;
        trie.assign(sz + 10, vector<int>(maxLet,0));
        finish.resize(sz + 10);
        paths.resize(sz+10);
    }

    void add(int x){
        int cur = 0;
        for(int i = 31; i >= 0; i--){
            int b = ( (x & (1 << i)) > 0);
            if(trie[cur][b] == 0)
                trie[cur][b] = nxt++;
            cur = trie[cur][b];
            paths[cur]++;
        }
        paths[cur]++;
    }

    void rem(int x){
       int cur = 0;
        for(int i = 31; i >= 0; i--){
            int b = ( (x & (1 << i)) > 0);
            cur = trie[cur][b];
            paths[cur]--;
        }
        finish[cur]--;
        paths[cur]--;
    }

    int query(int x){ //return the max xor with x
        int ans = 0, cur = 0;

        for(int i = 31; i >= 0; i--){
            int b = ( (x & (1 << i)) > 0);
            int bz = trie[cur][0];
            int bo = trie[cur][1];

            if(bz > 0 && bo > 0 && paths[bz] > 0 && paths[bo] > 0){
                //cout << "Optimal" << endl;
                cur = trie[cur][b ^ 1];
                ans += (1 << i);
            } else if(bz > 0 && paths[bz] > 0){
                //cout << "Zero" << endl;
                cur = trie[cur][0];
                if(b) ans += (1 << i);
            } else if(bo > 0 && paths[bo] > 0){
                //cout << "One" << endl;
                cur = trie[cur][1];
                if(!b) ans += (1 << i);
            } else {
                break;
            }
        }

        return ans;
    }

};
