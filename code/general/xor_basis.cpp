// XOR Basis
// You are given a set of $N$ integer values. You should find the minimum number of values that you need to add to the set such that the following will hold true:
// For every two integers $A$ and $B$ in the set, their bitwise xor $A \oplus B$ is also in the set.

vector<ll> basis;

void add(ll x) {
	for (int i = 0; i < (int)basis.size(); i++) {
        // reduce x using the current basis vectors
		x = min(x, x ^ basis[i]);
	}

	if (x != 0) { basis.push_back(x); }
}

ll res = (1LL << (int)basis.size()) - n;