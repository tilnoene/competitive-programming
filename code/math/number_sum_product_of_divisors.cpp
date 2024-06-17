// CSES - Divisor Analysis
// Print the number, sum and product of the divisors.
// Since the input number may be large, it is given as a prime factorization.
//
// Input:
// The first line has an integer n: the number of parts in the prime factorization.
// After this, there are n lines that describe the factorization. Each line has two numbers x and k where x is a prime and k is its power.
//
// Output:
// Print three integers modulo 10^9+7: the number, sum and product of the divisors.
//
// Constraints:
// (1 <= n <= 1e5) ; (2 <= x <= 1e6) ; (1 <= k <= 1e9) ; each x is a distinct prime

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll expo(ll base, ll pow) {
	ll ans = 1;
	while (pow) {
		if (pow & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		pow >>= 1;
	}
	return ans;
}

ll p[100001], k[100001];

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> p[i] >> k[i];
	ll div_cnt = 1, div_sum = 1, div_prod = 1, div_cnt2 = 1;
	for (int i = 0; i < n; i++) {
		div_cnt = div_cnt * (k[i] + 1) % MOD;
		div_sum = div_sum * (expo(p[i], k[i] + 1) - 1) % MOD *
		          expo(p[i] - 1, MOD - 2) % MOD;
		div_prod = expo(div_prod, k[i] + 1) *
		           expo(expo(p[i], (k[i] * (k[i] + 1) / 2)), div_cnt2) % MOD;
		div_cnt2 = div_cnt2 * (k[i] + 1) % (MOD - 1);
	}
	cout << div_cnt << ' ' << div_sum << ' ' << div_prod;
	return 0;
}