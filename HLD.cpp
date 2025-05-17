
struct SegTree {
    int n;                 
    vector<long long> t;   

    explicit SegTree(int N=0): n(N), t(2*N,0) {}
    void pointUpdate(int p,long long v){                    // O(log N)
        for(t[p+=n]=v; p>1; p>>=1) t[p>>1]=t[p]+t[p^1];
    }
    long long rangeQuery(int l,int r){                      // O(log N)
        long long res=0;
        for(l+=n, r+=n; l<=r; l>>=1, r>>=1){
            if(l&1) res+=t[l++];
            if(!(r&1)) res+=t[r--];
        }
        return res;
    }
};

struct HLD {
    int n, timer=0;
    vector<vector<int>> g;          
    vector<int>  parent, depth, sz; 
    vector<int>  head, pos;    
    SegTree seg;                 

    explicit HLD(int N): n(N), g(N), parent(N), depth(N),
                         sz(N), head(N), pos(N), seg(N) {}

    void addEdge(int u,int v){ g[u].push_back(v); g[v].push_back(u); }

    void dfsSize(int v,int p){
        parent[v]=p;  sz[v]=1;
        for(int &u: g[v]) if(u!=p){
            depth[u]=depth[v]+1;
            dfsSize(u,v);
            if(sz[u] > sz[g[v][0]])    
                swap(u, g[v][0]);        
            sz[v]+=sz[u];
        }
    }

  void dfsDecomp(int v,int h){
        head[v]=h;  pos[v]=timer++;         // position in the seg tree
        if(!g[v].empty() && g[v][0]!=parent[v])
            dfsDecomp(g[v][0],h);    
        for(int u: g[v])                    
            if(u!=parent[v] && u!=g[v][0]) dfsDecomp(u,u);
    }

    void build(int root=0){
        if(g[root].empty()) return;         
        depth[root]=0;
        dfsSize(root,-1);
        dfsDecomp(root,root);
    }

    template<class OP>
    void processChain(int u,int v, OP action){ // assumes depth[u] ≥ depth[v]
        while(head[u]!=head[v]){
            action(pos[head[u]], pos[u]);
            u = parent[head[u]];
        }
        action(pos[v], pos[u]);           
    }

    /* ========= PUBLIC API ========= */
    long long queryPath(int u,int v){
        long long ans=0;
        auto accumulate = [&](int l,int r){ ans += seg.rangeQuery(l,r); };
        if(depth[u] < depth[v]) swap(u,v);
        processChain(u, v, accumulate);       // u deeper than or equal v
        return ans;
    }

    void updatePath(int u,int v,long long add){
        auto apply = [&](int l,int r){    
            for(int i=l;i<=r;++i)       
                seg.pointUpdate(i, seg.rangeQuery(i,i)+add);
        };
        if(depth[u] < depth[v]) swap(u,v);
        processChain(u, v, apply);
    }
};
