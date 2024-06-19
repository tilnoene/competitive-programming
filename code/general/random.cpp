int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); //gerar int
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); //gerar ll

    /*usar rng() pra gerar numeros aleatórios.*/
    /*usar rng() % x pra gerar numeros em [0, x-1]*/
    for(int i = 0; i < 10; i++){
        cout << rng() << endl;
    }
    vector<ll> arr = {1,2,3,4,5,6,7,8,9};
    /*dá pra usar no shuffle de vector também*/
    shuffle(arr.begin(), arr.end(),rng);
    for(auto &x: arr) 
        cout << x << endl;

}
