
struct Line {
    ll b, m;

    Line(ll b, ll m) : m(m), b(b) {
        
    }

    ll q(ll x) {
        if (b >= INF) return INF;
        return m * x + b;
    }
};

struct LCT {
    ll l, r, mid;
    Line def = {INF, 0};
    LCT *left = nullptr, *right = nullptr;

    LCT(ll l, ll r) : l(l), r(r), mid((l + r) / 2) {
        if (r - l > 1) {
            left = new LCT(l, mid);
            right = new LCT(mid, r);
        }
    }

    void addSeg(Line x) {
        if (def.q(mid) > x.q(mid)) swap(x, def);
        if (r - l <= 1) return;
        if (x.m < def.m) right->addSeg(x);
        else left->addSeg(x);
    }

    ll q(ll x) {
        if (r - l <= 1)
            return def.q(x);
        if (x < mid)
            return min(left->q(x), def.q(x));
        return min(right->q(x), def.q(x));
    }
};
