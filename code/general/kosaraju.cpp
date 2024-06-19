// https://codeforces.com/blog/entry/125435
#ifdef MAXWELL_LOCAL_DEBUG
#include "debug/debug_template.cpp"
#define dbg debug
#else
#define debug(...)
#define dbg debug
#define debugArr(arr, n)
#endif

#include <bits/stdc++.h>
#define ff first
#define ss second

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

using tii = tuple<int,int,int>;
// auto [a,b,c] = ...
// .insert({a,b,c})

const int oo = (int)1e9 + 5; //INF to INT
const ll OO = 0x3f3f3f3f3f3f3f3fLL; //INF to LL

struct Kosaraju {

	int N;
	int cntComps;

	vector<vector<int>> g;
	vector<vector<int>> gi;

	stack<int> S;
	vector<int> vis;
	vector<int> comp;
	
	Kosaraju(vector<vector<int>>& arr) {
		N = (int)arr.size();
		cntComps = 0;

		g.resize(N);
		gi.resize(N);
		vis.resize(N);
		comp.resize(N);

		for(int i = 0; i < (int)arr.size(); i++) {
			for(auto &v : arr[i]) {
				g[i].push_back(v);
				gi[v].push_back(i);
			}
		}

		run();
	}

	void dfs(int u) {
		vis[u] = 1;
		for(auto &v : g[u]) if(!vis[v]) {
			dfs(v);
		}
		S.push(u);
	}

	void scc(int u, int c) {
		vis[u] = 1;
		comp[u] = c;
		for(auto &v : gi[u]) if(!vis[v]) {
			scc(v, c);
		}
	}

	void run() {
		vis.assign(N, 0);
		
		for(int i = 0; i < N; i++) if(!vis[i]) {
			dfs(i);
		}

		vis.assign(N, 0);

		while((int)S.size()) {
			int u = S.top();
			S.pop();
			if(!vis[u]) {
				scc(u, cntComps++);
			}
		}
	
	}

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    
    while(t--) {
        solve();
    }

}
