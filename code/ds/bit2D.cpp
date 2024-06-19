struct BIT2D {

    int n, m;
    vector<vector<int>> bit;

    BIT2D(int nn, int mm) { 
        //use as 0-indexed, but inside here I will use 1-indexed positions
        n = nn + 2;
        m = mm + 2;
        bit.assign(n, vector<int>(m));
    }

    void update(int x, int y, int p) {
        x++; y++;
        assert(x > 0 && y > 0 && x <= n && y <= m);
        for(; x < n; x += (x&(-x)))
            for(int j = y; j < m; j += (j&(-j)))
                bit[x][j] += p;
    }

    int sum(int x, int y) {
        int ans = 0; 
        for(; x > 0; x -= (x & (-x)))
            for(int j = y; j > 0; j -= (j&(-j)))
                ans += bit[x][j];
        return ans;
    }

    int query(int x, int y, int p, int q) {
        //x...p on line, y...q on column
        //sum from [x][y] to [p][q];
        x++; y++; p++; q++;
        assert(x > 0 && y > 0 && x <= n && y <= m);
        assert(p > 0 && q > 0 && p <= n && q <= m);
        return sum(p, q) - sum(x - 1, q) - sum(p, y - 1) + sum(x - 1, y - 1);
    }


};
