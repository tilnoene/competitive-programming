struct Sparse {
  
    vector<vector<int>> arr;

    int op(int& a, int& b){ //min, max, gcd, lcm, and, or
        return min(a,b);
        //return __gcd(a,b);
        //return max(a,b);
    }

    Sparse(vector<int>& v){ //Constrói a tabela
        int n = v.size(), logn = 0;
        while((1<<logn) <= n) logn++;
        arr.assign(n, vector<int>(logn, 0));
        for(int i = 0; i < n; i++)
            arr[i][0] = v[i];
        for(int k = 1; k < logn; k++){
            for(int i = 0; i < n; i++){
                if(i + ( 1 << k) -1 >= n)
                    break;
                int p = i+( 1 << (k-1) );                
                arr[i][k] = op( arr[i][ k-1 ] , arr[p][k-1]  );
            }
        }
    }

    int query(int l, int r){
        int pot = 31 - __builtin_clz(r-l+1); //r-l+1 são INTEIROS, não ll
        int k = (1 << pot) ;      
        return op(  arr[l][pot] , arr[  r - (k-1)  ][pot]   );
    }   
 
};