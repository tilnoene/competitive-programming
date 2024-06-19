vector<int> sieve(int MAXN){
    //list of prime numbers up to MAXN
    vector<int> primes;
    bitset<(int)1e7> not_prime;
    not_prime[0] = 1;
    not_prime[1] = 1;
    for(int i = 2; i <= MAXN; i++){
        if(!not_prime[i]){
            primes.push_back(i);
            for(ll j = 1LL * i * i; j <= MAXN; j += i){
                not_prime[(int)j] = 1;
            }
        }
    }
    return primes;
}

