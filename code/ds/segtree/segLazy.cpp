struct SegLazy {

    int n;
    vector<ll> seg;
    vector<ll> lazy;

    SegLazy(vector<ll>& arr){
        n = (int)arr.size();
        seg.assign(n+n+n+n, 0);
        lazy.assign(n+n+n+n, 0);
        build(1,0,n-1,arr);
    }

    ll merge(ll a, ll b){
        return a+b;
    }

    void build(ll x, int l, int r, vector<ll>& arr){
        if(l == r){
            seg[x] = 1LL * arr[l];
        } else {
            int mid = l + (r-l)/2;
            build(x+x, l, mid, arr);
            build(x+x+1, mid+1, r, arr);
            seg[x] = merge(seg[x+x], seg[x+x+1]);
        }
    }
    
    void upd_lazy(ll node, ll l, ll r){
        seg[node] += (ll)(r-l+1) * lazy[node];
        ll esq = node + node, dir = esq + 1;
        
        if(dir < (int)seg.size()){
            lazy[esq] += lazy[node];
            lazy[dir] += lazy[node];
        }
    
        lazy[node] = 0;
    }
    
    ll q(ll x, int l, int r, int i, int j){
        upd_lazy(x,l,r);
        
        if(r < i || l > j) 
            return 0;
        
        if(l >= i && r <= j ) 
            return seg[x];
        
        int mid = l + (r-l)/2;
        return merge(q(x+x,l,mid,i,j), q(x+x+1,mid+1,r,i,j));
    }
    
    ll query(int l, int r){ //valor em uma posi específica -> query de [l,l];
        return q(1, 0, n-1, l, r);
    }
    
    void upd(ll x, int l, int r, int i, int j, ll u){
        upd_lazy(x,l,r);
        if(r < i || l > j) return;
        if(l >= i && r <= j){
            lazy[x] += u;
            upd_lazy(x,l,r);
        } else {
            int mid = l + (r-l)/2;
            upd(x+x,l,mid,i,j,u);
            upd(x+x+1,mid+1,r,i,j,u);
            seg[x] = merge(seg[x+x], seg[x+x+1]);
        }
    }
    
    void upd_range(int l, int r, ll u){ //intervalo e valor
        upd(1,0,n-1,l,r,u);
    }

};