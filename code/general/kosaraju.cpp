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