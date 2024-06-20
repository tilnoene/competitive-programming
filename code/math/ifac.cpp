// inverse of factorial

mint fac[N], ifac[N];

void build_fac() {
    fac[0] = 1;

    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i;
    }

    ifac[N - 1] = inv(fac[N - 1]);

    for (int i = N - 2; i >= 0; i--) {
        ifac[i] = ifac[i + 1] * (i + 1);
    }
}