template<typename T> //use as SegtreeHash<int> h or SegtreeHash<char>
struct SegtreeHash {
 
    int n; //size do array que a seg vai ser criada em cima

    // P = 31, 53, 59, 73 .... (prime > number of different characters)
    // M = 578398229, 895201859, 1e9 + 7, 1e9 + 9 (big prime)
    int p, m;

    vector<ll> seg, pot;

    ll minValue = 0; // menor valor possível que pode estar na estrutura
                     // isso é pra evitar que a hash de '0' seja igual a de '0000...'

    SegtreeHash(vector<T>& s, ll P = 31, ll MOD = (ll)1e9 + 7){
        n = (int)s.size();
        p = P; m = MOD;
        seg.resize(4 * n, -1);
        pot.resize(4 * n);
        pot[0] = 1;
        for(int i = 1; i < (int)pot.size(); i++) {
            pot[i] = (pot[i - 1] * P) % MOD;
        }
        seg_build(1, 0, n - 1, s);
    }
 
    ll merge(ll a, ll b, int tam){
        if(a == -1) return b;
        if(b == -1) return a;
        return (a + b * pot[tam]) % m;
    }
 
    void seg_build(int x, int l, int r, vector<T>& s){
        if(r < l) return;
        if(l == r){
            seg[x] = (int)s[l] - minValue + 1;
        } else {
            int mid = l + (r-l)/2;
            seg_build(x+x, l, mid, s);
            seg_build(x+x+1, mid+1, r, s);
            seg[x] = merge(seg[x+x], seg[x+x+1], mid - l + 1);
        }
    }
 
    //nó atual, intervalo na árvore e intervalo pedido
    ll q(int x, int l, int r, int i, int j){
        if(r < i || l > j ) return -1;
        if(l >= i && r <= j ) return seg[x];
        int mid = l + (r-l)/2;        
        return merge(q(x+x,l,mid,i,j), q(x+x+1,mid+1,r,i,j), mid - max(i, l) + 1);
    }
 
    //att posi pra val
    void att(int x, int l, int r, int posi, T val){
        if(l == r){
            seg[x] = (int)val - minValue + 1;
        } else {
            int mid = l + (r-l)/2;
            if(posi <= mid)att(x+x,l,mid,posi,val);    
            else att(x+x+1,mid+1,r,posi,val);
            seg[x] = merge(seg[x+x], seg[x+x+1], mid - l + 1);
        }
    }
 
    ll query(int l, int r){
        return q(1, 0, n-1, l, r);
    }
 
    void update(int posi, T val){ //alterar em posi pra val
        att(1, 0, n-1, posi, val);
    }
 
};