struct PSum {

    vector<vi> arr;
    int n, m, initialized = 0;

    PSum(int _n, int _m) {
        n = _n;
        m = _m;
        arr.resize(n + 2);
        arr.assign(n + 2, vector<int>(m + 2, 0));
    }

    void add(int a, int b, int c) {
        //a and b are 0-indexed
        arr[a + 1][b + 1] += c;
    }

    void init() {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                arr[i][j] += arr[i][j - 1];
                arr[i][j] += arr[i - 1][j];
                arr[i][j] -= arr[i - 1][j - 1];
            }
        }
        initialized = 1;
    }

    int query(int a, int b, int c, int d) {
        // sum of a...c and b...d
        // a, b, c and d are 0-indexed
        assert(initialized);
        return arr[c + 1][d + 1] - arr[a][d + 1] - arr[c + 1][b] + arr[a][b];
    }

};
