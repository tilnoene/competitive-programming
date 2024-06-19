struct BIT {
    int n, LOGN = 0;
    vector<ll> bit;

    BIT(int nn){
        n = nn + 10;
        bit.resize(n + 10, 0);
        while( (1LL << LOGN) <= n ) LOGN++;
    }

    ll query(int x){
        x++;
        ll ans = 0;
        while(x > 0){
            ans += bit[x];
            x -= (x & (-x));
        }
        return ans;
    }

    void update(int x, ll val){
        x++;
        while(x < (int)bit.size()){
            bit[x] += val;
            x += (x & (-x));
        }
    }

    int findkth(int k){
        //kth smallest, O(logN)
        //use position i to count how many times value 'i' appear
        int sum = 0, pos = 0;
        for(int i = LOGN; i >= 0; i--){
            if(pos + (1LL << i) < n && sum + bit[pos + (1LL << i)] < k){
                sum += bit[pos + (1LL << i)];
                pos += (1LL << i);
            }
        }
        return pos;
    }
/*
    int findkth(int k){
        //kth smallest, O(log^2(N))
        //use position i to count how many times value 'i' appear
        int x = 0, mx = 200;
        for(int b = n; b > 0 && mx > 0; b /= 2){
            while( x+b < n && query(x+b) < k && mx-- > 0 ){
                x += b;
            }
        }
        return x+1;
    }
*/
};
