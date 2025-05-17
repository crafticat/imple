
struct Treap {
    char c; double p; int s; Treap *ls,*rs;
    Treap(char x): c(x), p(rand()), s(1), ls(nullptr), rs(nullptr) {}
    void print(){ if(ls) ls->print(); cout<<c; if(rs) rs->print(); }
};

int sz(Treap* t){ return t ? t->s : 0; }
void upsz(Treap* t){ if(t) t->s = 1 + sz(t->ls) + sz(t->rs); }
int ind(Treap* t){ return t ? sz(t->ls) + 1 : -1; }

void merge(Treap*& t, Treap* a, Treap* b){
    if(!a || !b){ t = a ? a : b; return; }
    if(a->p > b->p){ merge(a->rs, a->rs, b); t = a; }
    else           { merge(b->ls, a, b->ls); t = b; }
    upsz(t);
}

void split(Treap* t, Treap*& a, Treap*& b, int k){
    if(!t){ a = b = nullptr; return; }
    if(ind(t) <= k){ split(t->rs, t->rs, b, k - ind(t)); a = t; }
    else           { split(t->ls, a, t->ls, k);           b = t; }
    upsz(a); upsz(b);
}

void prnt(Treap* t){ if(t) t->print(); cout << '\n'; }

void cap(Treap*& t, int a, int b){
    trp *x = nullptr, *y = nullptr, *z = nullptr;
    split(t, y, z, b);
    split(y, x, y, a - 1);
    merge(t, x, z);
    merge(t, t, y);
}
