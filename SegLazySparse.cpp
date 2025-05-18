
struct Seg {
    Seg *left = nullptr, *right = nullptr;
    int l, r, mid, v = 0, lazy = 0;
    bool sparse = false;

    Seg(int l , int r) : l(l) ,r(r) {}
    void push() {
        v += lazy * (r - l);
        if (r - l > 1) {
            left->lazy+=lazy;
            right->lazy +=lazy;
        }
        lazy = 0;
        
        if (sparse) return;
        sparse = 1;
        
        if (r - l > 1) {
            left = new Seg(l, mid);
            right =new Seg(mid, r);
        }
    }

    int q(int a ,int b) {
        push();
        if (b <= l or a >= r) return 0;
        if (a <= l and b >= r) return v;
        return left->q(a,b) + right->q(a,b);
    }

    void addR(int a, int b, int u) {
        push();
        if (b <= l or a >= r) return;
        if (a <= l and b >= r) {
            lazy += u;
            push();
            return;
        }
        left->addR(a,b, u),right->addR(a,b, u);
    }
};
