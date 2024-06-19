struct MaxQueue {
    stack< pair<ll,ll> > in, out;
 
    void add(ll x){
        if(in.size())
            in.push( { x, max(x, in.top().ss)  } );
        else
            in.push( {x, x} );
    }
 
   
    ll get_max(){
        if(in.size() > 0 && out.size() > 0)
            return max(in.top().ss, out.top().ss);
        else if(in.size() > 0) return in.top().ss;
        else if(out.size() > 0) return out.top().ss;
        else return INF;
    }
 
 
    void rem(){
 
        if(out.size() == 0){
            while(in.size()){
                ll temp = in.top().ff, ma;
                if(out.size() == 0) ma = temp;
                else ma = max(temp, out.top().ss);
                out.push({temp, ma});
                in.pop();
            }
        }
        //removendo o topo de out
        out.pop();
    }
 
    ll size(){
        return in.size() + out.size();
    }
 
};
