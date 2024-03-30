struct Hash {
    ll MOD, P;
    int n; string s;
    vector<ll> h, hi, p;
    Hash() {}
    Hash(string s, ll MOD, ll P = 31): s(s), MOD(MOD), P(P), n(s.size()), h(n), hi(n), p(n) {
        for (int i=0;i<n;i++) p[i] = (i ? P*p[i-1]:1) % MOD;
        for (int i=0;i<n;i++)
            h[i] = (s[i] + (i ? h[i-1]:0) * P) % MOD;
        for (int i=n-1;i>=0;i--) 
            hi[i] = (s[i] + (i+1<n ? hi[i+1]:0) * P) % MOD;
    }
    int query(int l, int r) {
        ll hash = (h[r] - (l ? h[l-1]*p[r-l+1]%MOD : 0));
        return hash < 0 ? hash + MOD : hash;
    }
    int query_inv(int l, int r) {
        ll hash = (hi[l] - (r+1 < n ? hi[r+1]*p[r-l+1] % MOD : 0));
        return hash < 0 ? hash + MOD : hash;
    }
};

struct DoubleHash {
    const ll MOD1 = 90264469;
    const ll MOD2 = 25699183;

    Hash hash1, hash2;

    DoubleHash();

    DoubleHash(string s) : hash1(s, MOD1), hash2(s, MOD2) {}

    pair<int, int> query(int l, int r) {
        return { hash1.query(l, r), hash2.query(l, r) };
    }

    pair<int, int> query_inv(int l, int r) {
        return { hash1.query_inv(l, r), hash2.query_inv(l, r) };
    }
};

struct TripleHash {
    const ll MOD1 = 90264469;
    const ll MOD2 = 25699183;
    const ll MOD3 = 81249169;

    Hash hash1, hash2, hash3;

    TripleHash();

    TripleHash(string s) : hash1(s, MOD1), hash2(s, MOD2), hash3(s, MOD3) {}

    tuple<int, int, int> query(int l, int r) {
        return { hash1.query(l, r), hash2.query(l, r), hash3.query(l, r) };
    }

    tuple<int, int, int> query_inv(int l, int r) {
        return { hash1.query_inv(l, r), hash2.query_inv(l, r), hash3.query_inv(l, r) };
    }
};

struct HashK {
    vector<ll> primes; // more primes = more hashes
    vector<Hash> hash;
 
    HashK();
 
    HashK(string s, vector<ll> primes): primes(primes) {
        for (auto p : primes) {
            hash.push_back(Hash(s, p));
        }
    }
 
    vector<int> query(int l, int r) {
        vector<int> ans;
 
        for (auto h : hash) {
            ans.push_back(h.query(l, r));
        }
 
        return ans;
    }
 
    vector<int> query_inv(int l, int r) {
        vector<int> ans;
 
        for (auto h : hash) {
            ans.push_back(h.query_inv(l, r));
        }
 
        return ans;
    }
};