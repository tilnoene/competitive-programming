struct Trie {

    struct Node {
        map<char, Node> adj; // dá pra trocar por vector(26)
        ll finishHere;

        Node() {
            finishHere = 0;
        }

        bool find(char c) {
            return adj.find(c) != adj.end();
        }

    };

    Node mainNode;

    Trie(){
        mainNode = Node();
    }

    void add(string &s) {
        Node *curNode = &mainNode;

        for(auto &c : s) {
            
            if(!curNode->find(c)) {
                curNode->adj[c] = Node();
            }

            curNode = &curNode->adj[c];
        }

        curNode->finishHere += 1;
    }

    void dfs(Node& node) {
        for(auto &v : node.adj) {
            dfs(v.ss);
            // faz alguma coisa
        }
    }

    void dfs() {
        return dfs(mainNode);
    }

    bool search(string &s) {
        Node* curNode = &mainNode;

        for(auto &c : s) {
            if(!curNode->find(c))
                return false;

            curNode = &curNode->adj[c];
        }

        return curNode->finishHere > 0;
    }

    void debugRec(Node node, int depth) {
        for(auto &x : node.adj) {
            cout << string(3 * depth, ' ') << x.ff << " " << x.ss.finishHere << "\n";
            debugRec(x.ss, depth + 1);
        }
    }

    void debug() {
        debugRec(mainNode, 0);
    }

};
