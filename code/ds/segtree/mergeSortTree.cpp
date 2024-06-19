//const int MAXN = 3e5 + 10;
//vector<int> seg[ 4 * MAXN + 10];

struct MergeSortTree {

    int n; //size do array que a seg vai ser criada em cima
    vector< vector<int> > seg;
    //vector< vector<ll> > ps; //prefix sum

    MergeSortTree(vector<int>& s){
        //se o input for grande (ou o tempo mt puxado), coloca a seg com size
        //maximo de forma global
        n = (int)s.size();
        seg.resize(4 * n + 10);  
        //ps.resize(4 * n + 10);    
        seg_build(1,0,n-1,s);
    }

    vector<int> merge(vi& a, vi& b){
        int i = 0, j = 0, p = 0;
        vi ans(a.size() + b.size());
        while(i < (int)a.size() && j < (int)b.size()){
            if(a[i] < b[j]){
                ans[p++] = a[i++];
            } else {
                ans[p++] = b[j++];
            }
        }
        while(i < (int)a.size()){
            ans[p++] = a[i++];
        }
        while(j < (int)b.size()){
            ans[p++] = b[j++];
        }
        return ans;
    }

    vector<ll> calc(vi& s) {
        ll sum = 0;
        vector<ll> tmp;
        for(auto &x : s) {
            sum += x;
            tmp.push_back(sum);
        }
        return tmp;
    }

    void seg_build(int x, int l, int r, vector<int>& s){
        if(r < l) return;
        if(l == r){
            seg[x].push_back(s[l]);
            //ps[x] = {s[l]};
        } else {
            int mid = l + (r-l)/2;
            seg_build(x+x, l, mid, s);
            seg_build(x+x+1, mid+1, r, s);
            seg[x] = merge(seg[x+x], seg[x+x+1]);
            //ps[x] = calc(seg[x]);
        }
    }

    //nó atual, intervalo na árvore e intervalo pedido
    // retorna a quantidade de numeros <= val em [l, r]
    
    ll q(int x, int l, int r, int i, int j, int val){
        if(r < i || l > j ) return 0;
        if(l >= i && r <= j ){
            return (lower_bound(seg[x].begin(), seg[x].end(), val)  - seg[x].begin());
        }
        int mid = l + (r-l)/2;        
        return q(x+x,l,mid,i,j, val) + q(x+x+1,mid+1,r,i,j, val);
    }
    

    // retorna a soma dos numeros <= val em [l, r]
    // nó atual, intervalo na árvore e intervalo pedido
    /*
    ll q(int x, int l, int r, int i, int j, ll val){
        if(r < i || l > j ) return 0;
        if(l >= i && r <= j ){
            auto it = upper_bound(seg[x].begin(), seg[x].end(), val) - seg[x].begin();

            if(val > seg[x].back()) {
                return ps[x].back();
            }

            if(val < seg[x][0]) {
                return 0;
            }

            return ps[x][it - 1];

        }

        int mid = l + (r-l)/2;        
        return q(x+x,l,mid,i,j, val) + q(x+x+1,mid+1,r,i,j, val);
    }
    */

    ll query(int l, int r, ll val){
        return q(1, 0, n-1, l, r, val);
    }

};
