struct QueryTree {
    int n, t = 0, l = 3, build = 0, euler = 0;
    vector<ll> dist;
    vector<int> in, out, d;
    vector<vector<int>> sobe;
    vector<vector<pair<int,ll>>> arr;
    vector<vector<ll>> table_max; //max edge
    vector<vector<ll>> table_min; //min edge

    QueryTree(int nn) {
        n = nn + 5;
        arr.resize(n);
        in.resize(n);
        out.resize(n);
        d.resize(n);
        dist.resize(n);
        while( (1 << l) < n ) l++;
        sobe.assign(n + 5, vector<int>(++l));
        table_max.assign(n + 5, vector<ll>(l));
        table_min.assign(n + 5, vector<ll>(l));
    }

    void add_edge(int u, int v, ll w){ //bidirectional edge with weight w
        arr[u].push_back({v, w});
        arr[v].push_back({u, w});
    }

    //assert the root of tree is node 1 or change the 'last' in the next function
    void Euler_Tour(int u, int last = 1, ll we = 0, int depth = 0, ll sum = 0){ //euler tour
        euler = 1; //remember to use this function before the queries
        in[u] = t++;
        d[u] = depth;
        dist[u] = sum; //sum = sum of the values in edges from root to node u
        sobe[u][0] = last; //parent of u. parent of 1 is 1
        table_max[u][0] = we;
        table_min[u][0] = we;
        for(auto v: arr[u]) if(v.ff != last){
            Euler_Tour(v.ff, u, v.ss, depth + 1, sum + v.ss);
        }
        out[u] = t++;
    }

    void build_table(){ //binary lifting
        assert(euler);
        build = 1; //remeber use this function before queries
        for(int k = 1; k < l; k++){
            for(int i = 1; i <= n; i++){
                sobe[i][k] = sobe[sobe[i][k-1]][k-1];
                table_max[i][k] = max(table_max[i][k - 1], table_max[sobe[i][k-1]][k-1]);
                table_min[i][k] = min(table_min[i][k - 1], table_min[sobe[i][k-1]][k-1]);
            }
        }
    }

    int is_ancestor(int u, int v){ // return 1 if u is ancestor of v
        assert(euler);
        return in[u] <= in[v] && out[u] >= out[v];
    }

    int lca(int u, int v){ //return lca of u and v
        assert(build && euler);
        if(is_ancestor(u,v)) return u;
        if(is_ancestor(v,u)) return v;
        int lca = u;
        for(int k = l - 1; k >= 0; k--){
            int tmp = sobe[lca][k];
            if(!is_ancestor(tmp, v)){
                lca = tmp;
            }
        }
        return sobe[lca][0];
    }

    int lca(int u, int v, int root) { //return lca of u and v when tree is rooted at 'root'
        return lca(u, v) ^ lca(v, root) ^ lca(root, u); //magic
    }

    int up_k(int u, int qt){ //return node k levels higher starting from u
        assert(build && euler);
        for(int b = 0; b < l; b++){
            if(qt%2) u = sobe[u][b];
            qt >>= 1;
        }
        return u;
    }

    ll goUpMax(int u, int to){ //return the max weigth of a edge going from u to 'to'
        assert(build);
        if(u == to) return 0;
        ll mx = table_max[u][0];
        for(int k = l - 1; k >= 0; k--){
            int tmp = sobe[u][k];
            if( !is_ancestor(tmp, to) ){
                mx = max(mx, table_max[u][k]);
                u = tmp;
            }
        }
        return max(mx, table_max[u][0]);
    }

    ll max_edge(int u, int v){ //return the max weight of a edge in the simple path from u to v
        assert(build);
        int ancestor = lca(u, v);
        ll a = goUpMax(u, ancestor), b = goUpMax(v, ancestor);
        if(ancestor == u) return b;
        else if(ancestor == v) return a;
        return max(a,b);
    }

    ll goUpMin(int u, int to){ //return the min weight of a edge going from u to 'to'
        assert(build);
        if(u == to) return oo;
        ll mx = table_min[u][0];
        for(int k = l - 1; k >= 0; k--){
            int tmp = sobe[u][k];
            if( !is_ancestor(tmp, to) ){
                mx = min(mx, table_min[u][k]);
                u = tmp;
            }
        }
        return min(mx, table_min[u][0]);
    }

    ll min_edge(int u, int v){ //return the min weight of a edge in the simple path from u to v
        assert(build);
        int ancestor = lca(u, v);
        ll a = goUpMin(u, ancestor), b = goUpMin(v, ancestor);
        if(ancestor == u) return b;
        else if(ancestor == v) return a;
        return min(a,b);
    }

    ll query_dist(int u, int v){ //distance of nodes u and v
        int x = lca(u, v);
        return dist[u] - dist[x] + dist[v] - dist[x];
    }

    int kth_between(int u, int v, int k){ //kth node in the simple path from u to v; if k = 1, ans = u
        k--;
        int x = lca(u, v);
        if( k > d[u] - d[x] ){
            k -= (d[u] - d[x]);
            return up_k(v, d[v]-d[x]-k);
        }
        return up_k(u, k);
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1, n, u, v, w, k;
    string s;
    cin >> t;
    while(t--){
        cin >> n;
        QueryTree arr(n);
        for(int i = 1; i < n; i++){
            cin >> u >> v >> w;
            arr.add_edge(u,v,w);
        }
        arr.Euler_Tour(1);
        arr.build_table();
        while(cin >> s, s != "DONE"){
            cin >> u >> v;
            if(s == "DIST") {
                cout << arr.query_dist(u, v) << "\n";
            } else {
                cin >> k;
                cout << arr.kth_between(u,v,k) << "\n";
            }
        }
        cout << "\n";
    }

}