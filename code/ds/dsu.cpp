// DSU
// 
// https://judge.yosupo.jp/submission/126864

struct DSU {
    int n = 0, components = 0;
    vector<int> parent;
    vector<int> size;

    DSU(int nn){
        n = nn;
        components = n;
        size.assign(n + 5, 1);
        parent.assign(n + 5, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x){
        if(x == parent[x]) {
            return x;
        }
        //path compression
        return parent[x] = find(parent[x]); 
    }

    void join(int a, int b){
        a = find(a); 
        b = find(b);

        if(a == b) {
            return;
        } 
        
        if(size[a] < size[b]) {
            swap(a, b);
        }
        
        parent[b] = a;
        size[a] += size[b];
        components -= 1;
    }
    
    int sameSet(int a, int b) {
        a = find(a);
        b = find(b);
        return a == b;
    }
};