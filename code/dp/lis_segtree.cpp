int n, arr[MAX], aux[MAX]; cin >> n;
for (int i = 0; i < n; i++) {
    cin >> arr[i];
    aux[i] = arr[i];
}

sort(aux, aux+n);

Segtree st(n); // seg of maximum

int ans = 0;
for (int i = 0; i < n; i++) {
    int it = lower_bound(aux, aux+n, arr[i]) - aux;
    int lis = st.query(0, it) + 1;

    st.update(it, lis);

    ans = max(ans, lis);
}

cout << ans << '\n';