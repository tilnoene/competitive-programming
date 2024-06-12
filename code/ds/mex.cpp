// Mex
//
// facilita queries de mex com update
//
// N eh o maior valor possível do mex
// add(x) = adiciona x
// rem(x) = remove x
//
// O(log N) por insert
// O(1) por query

struct Mex {
    map<int, int> cnt;
    set<int> possible;

    Mex(int n) {
        for (int i = 0; i <= n + 1; i++) {
            possible.insert(i);
        }
    }

    void add(int x) {
        cnt[x]++;
        possible.erase(x);
    }

    void rem(int x) {
        cnt[x]--;
        
        if (cnt[x] == 0) {
            possible.insert(x);
        }
    }

    int query() {
        return *(possible.begin());
    }
};