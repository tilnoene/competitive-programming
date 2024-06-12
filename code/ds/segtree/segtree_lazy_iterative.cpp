// Segtree iterativa com lazy
// 
// https://codeforces.com/gym/103708/problem/C
// 
// O(N * log(N)) build
// O(log(N)) update e query

const int MAX = 524288; // NEED TO BE POWER OF 2 !!!
const int LOG = 19; // LOG = ceil(log2(MAX))

namespace seg {
    ll seg[2*MAX], lazy[2*MAX];
    int n;
 
    ll junta(ll a, ll b) {
        return a+b;
    }
 
    // soma x na posicao p de tamanho tam
    void poe(int p, ll x, int tam, bool prop=1) {
        seg[p] += x*tam;
        if (prop and p < n) lazy[p] += x;
    }
 
    // atualiza todos os pais da folha p
    void sobe(int p) {
        for (int tam = 2; p /= 2; tam *= 2) {
            seg[p] = junta(seg[2*p], seg[2*p+1]);
            poe(p, lazy[p], tam, 0);
        }
    }
 
    void upd_lazy(int i, int tam) {
        if (lazy[i] && (2 * i + 1) < 2 * MAX) {
            poe(2*i, lazy[i], tam);
            poe(2*i+1, lazy[i], tam);
            lazy[i] = 0;
        }
    }
 
    // propaga o caminho da raiz ate a folha p
    void prop(int p) {
        int tam = 1 << (LOG-1);
        for (int s = LOG; s; s--, tam /= 2) {
            int i = p >> s;
            upd_lazy(i, tam);
        }
    }
 
    void build(int n2) {
        n = n2;
        for (int i = 0; i < n; i++) seg[n+i] = 0;
        for (int i = n-1; i; i--) seg[i] = junta(seg[2*i], seg[2*i+1]);
        for (int i = 0; i < 2*n; i++) lazy[i] = 0;
    }
 
    ll query(int a, int b) {
        ll ret = 0;
        for (prop(a+=n), prop(b+=n); a <= b; ++a/=2, --b/=2) {
            if (a%2 == 1) ret = junta(ret, seg[a]);
            if (b%2 == 0) ret = junta(ret, seg[b]);
        }
        return ret;
    }
 
    void update(int a, int b, int x) {
        int a2 = a += n, b2 = b += n, tam = 1;
        for (; a <= b; ++a/=2, --b/=2, tam *= 2) {
            if (a%2 == 1) poe(a, x, tam);
            if (b%2 == 0) poe(b, x, tam);
        }
        sobe(a2), sobe(b2);
    }
 
    int findkth(int x, int l, int r, ll k, int tam){
        int esq = x + x;
        int dir = x + x + 1;
 
        upd_lazy(x, tam);
        upd_lazy(esq, tam/2);
        upd_lazy(dir, tam/2);
 
        if(l == r){
            return l;
        } else {
            int mid = l + (r-l)/2;
 
            if(seg[esq] >= k){
                return findkth(esq,l,mid,k, tam/2);
            } else {
                return findkth(dir,mid+1, r, k - seg[esq], tam/2);    
            }
        }
    }
 
    int findkth(ll k){
        // kth smallest, O(logN)
        // use position i to count how many times value 'i' appear
        // merge must be the sum of nodes
        return findkth(1,0,n-1,k,(1 << (LOG-1)));
    }
};