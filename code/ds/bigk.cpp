struct SetSum {
    ll sum;
    multiset<ll> ms;

    SetSum() {}

    void add(ll x) {
        sum += x;
        ms.insert(x);
    }

    int rem(ll x) {
        auto it = ms.find(x);

        if (it == ms.end()) {
            return 0;
        }

        sum -= x;
        ms.erase(it);
        return 1;
    }

    ll getMin() { return *ms.begin(); }

    ll getMax() { return *ms.rbegin(); }

    ll getSum() { return sum; }

    int size() { return (int)ms.size(); }
};

struct BigK {
    int k;
    SetSum gt, mt;

    BigK(int k): k(k) {}

    void balance() {
        while (gt.size() > k) {
            ll mn = gt.getMin();
            gt.rem(mn);
            mt.add(mn);
        }

        while (gt.size() < k && mt.size() > 0) {
            ll mx = mt.getMax();
            mt.rem(mx);
            gt.add(mx);
        }
    }

    void add(ll x) {
        gt.add(x);
        balance();
    }

    void rem(ll x) {
        if (mt.rem(x) == 0) {
            gt.rem(x);
        }

        balance();
    }

    // be careful, O(abs(oldK - newk) * log)
    void setK(int _k) {
        k = _k;
        balance();
    }

    // O(log)
    void incK() { setK(k + 1); }
    
    // O(log)
    void decK() { setK(k - 1); }
};