struct Node {

    int l, r;

    int pref0, suf0, best0;
    int pref1, suf1, best1;

    Node(){
        pref0 = 0; suf0 = 0; best0 = 0;
        pref1 = 0; suf1 = 0; best1 = 0;
        l = -1; r = -1;
    };

    void Init(int val_, int l_, int r_) {
        best0 = !val_;
        pref0 = !val_;
        suf0 = !val_;
        
        best1 = val_;
        pref1 = val_;
        suf1 = val_;
        
        l = l_; 
        r = r_;
    }


    bool AllZero() {
        return r - l + 1 == best0;
    }

    bool AllOne() {
        return r - l + 1 == best1;
    }

    void Reverse() {
        swap(pref0, pref1);
        swap(suf0, suf1);
        swap(best0, best1);
    }

};

Node Merge(Node a, Node b) {

    if(a.l == -1 || a.r == -1) {
        return b;
    }

    if(b.l == -1 || b.r == -1) {
        return a;
    }

    auto ans = Node();

    ans.l = a.l;
    ans.r = b.r;

    // --------------------------------------------- // 


    if(a.AllZero()) {
        ans.pref0 = a.pref0 + b.pref0;
    } else {
        ans.pref0 = a.pref0;
    }

    if(b.AllZero()) {
        ans.suf0 = b.suf0 + a.suf0;
    } else {
        ans.suf0 = b.suf0;
    }

    ans.best0 = max({
        a.best0,
        b.best0,
        a.suf0 + b.pref0
    });

    // --------------------------------------------- // 


    if(a.AllOne()) {
        ans.pref1 = a.pref1 + b.pref1;
    } else {
        ans.pref1 = a.pref1;
    }

    if(b.AllOne()) {
        ans.suf1 = b.suf1 + a.suf1;
    } else {
        ans.suf1 = b.suf1;
    }

    ans.best1 = max({
        a.best1,
        b.best1,
        a.suf1 + b.pref1
    });

    // --------------------------------------------- // 

    return ans;
}

  
struct SegLazy {

    private:

        int n;
        vector<Node> seg;
        vector<bool> lazy; // precisa reverter ou nao


        void build(ll x, int l, int r, string& s){
            if(l == r){
                int val = s[l] - '0';
                seg[x].Init(val, l, r);
            } else {
                int mid = l + (r-l)/2;
                build(x+x, l, mid, s);
                build(x+x+1, mid+1, r, s);
                seg[x] = Merge(seg[x+x], seg[x+x+1]);
            }
        }
        
        void upd_lazy(ll node, ll l, ll r){

            if(lazy[node]) {
                seg[node].Reverse();
            }

            ll esq = node + node, dir = esq + 1;
            
            if(dir < (int)seg.size() && lazy[node]){
                lazy[esq] = !lazy[esq];
                lazy[dir] = !lazy[dir]; 
            }
        
            lazy[node] = 0;
        }
        
        Node q(ll x, int l, int r, int i, int j){
            upd_lazy(x,l,r);
            
            if(r < i || l > j) 
                return Node();
            
            if(l >= i && r <= j ) 
                return seg[x];
            
            int mid = l + (r-l)/2;
            return Merge(q(x+x,l,mid,i,j), q(x+x+1,mid+1,r,i,j));
        }
        
        void upd(ll x, int l, int r, int i, int j){
            upd_lazy(x,l,r);
            if(r < i || l > j) return;
            if(l >= i && r <= j){
                lazy[x] = !lazy[x];
                upd_lazy(x,l,r);
            } else {
                int mid = l + (r-l)/2;
                upd(x+x,l,mid,i,j);
                upd(x+x+1,mid+1,r,i,j);
                seg[x] = Merge(seg[x+x], seg[x+x+1]);
            }
        }


    public:

        SegLazy(string& s){
            n = (int)s.size();
            seg.assign(n+n+n+n, Node());
            lazy.assign(n+n+n+n, 0);
            build(1,0,n-1,s);
        }

        
        void update(int l){
            upd(1,0,n-1,l,l);
        }

        void update_range(int l, int r){
            upd(1,0,n-1,l,r);
        }

        Node query(int l){
            return q(1, 0, n-1, l, l);
        }

        Node query(int l, int r){
            return q(1, 0, n-1, l, r);
        }

};

void solve() {  

    int n, q;
    string s;

    cin >> n >> q >> s;

    SegLazy seg(s);

    while(q--) {
        int c, l, r;
        cin >> c >> l >> r;

        if(c == 1) {
            // inverte l...r
            seg.update_range(l - 1, r - 1);
        } else {    
            // query l...r
            auto node = seg.query(l - 1, r - 1);
            cout << node.best1 << "\n";
        }

    }    

}