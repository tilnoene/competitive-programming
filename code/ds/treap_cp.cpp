mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
 
typedef struct item * pitem;
 
struct item {
    int prior, value, cnt;
    bool rev;
    pitem l, r;
 
    // Construtor para inicializar um nó com um valor dado
    item(int _val) {
        prior = rng();
        value = _val;
        cnt = 1; // Inicializa o contador como 1
        rev = false; // Define o reverso como falso por padrão
        l = r = nullptr;
    }
};
 
int cnt (pitem it) {
	return it ? it->cnt : 0;
}
 
void upd_cnt (pitem it) {
	if (it)
		it->cnt = cnt(it->l) + cnt(it->r) + 1;
}
 
void push (pitem it) {
	if (it && it->rev) {
		it->rev = false;
		swap (it->l, it->r);
		if (it->l)  it->l->rev ^= true;
		if (it->r)  it->r->rev ^= true;
	}
}
 
void merge (pitem & t, pitem l, pitem r) {
	push (l);
	push (r);
	if (!l || !r)
		t = l ? l : r;
	else if (l->prior > r->prior)
		merge (l->r, l->r, r),  t = l;
	else
		merge (r->l, l, r->l),  t = r;
	upd_cnt (t);
}
 
// essa func quebra um range baseado na key e salva as duas partes em l, r
void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
	if (!t)
		return void( l = r = 0 );
	push (t);
	int cur_key = add + cnt(t->l);
	if (key <= cur_key)
		split (t->l, l, t->l, key, add),  r = t;
	else
		split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
	upd_cnt (t);
}
 
// essa inverte o range l, r do nó t
void reverse (pitem t, int l, int r) {
	pitem t1, t2, t3;
	split (t, t1, t2, l);
	split (t2, t2, t3, r-l+1);
	t2->rev ^= true;
	merge (t, t1, t2);
	merge (t, t, t3);
}
 
vector<int> ans;
 
void output (pitem t) {
	if (!t)  return;
	push (t);
	output (t->l);
    // pode printar o valor direto aq tmb
	ans.push_back(t->value);
	output (t->r);
}

// https://cses.fi/problemset/task/2072/
// cortar o range [l, r] e cola no final
void cut_and_paste(pitem root, int l, int r) {
    pitem A, B, C, D;
    // separa a root em caras com indice < l r >= l 
    //e salva as partes em A, B
    split(root, A, B, l);
    // pega a parte B (indices i >= l) e pega 
    // exatamente o tamanho que vc quer
    // salva as partes em C e D
    split(B, C, D, r - l + 1);
    // Da merge dos indices i < l com a parte i > r
    merge(root, A, D);
    // da merge do pedaço que vc queria final e deixa salvo em root
    merge(root, root, C);
}
 
void solve() {  
 
    int n, q;
    cin >> n >> q;
 
    string s;
    cin >> s;
    
    pitem root = nullptr;
 
    for(int i = 0; i < n; i++) {
        pitem newNode = new item(i);
        merge(root, root, newNode);
    }
 
    while(q--) {
        int l, r;
        cin >> l >> r;
        cut_and_paste(root, l - 1, r - 1);
    }
    
    output(root);
 
    for(int i = 0; i < n; i++) {
        cout << s[ans[i]];
    }
    
    cout << "\n";
 
}
