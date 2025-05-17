
struct Line {
    ll m, b;
    Line(ll m, ll b) : m(m), b(b) {}
    Line() = default;

    ll get(ll x) {
        return m * x + b;
    }
};

// Checks if a intersect b happends before b intersects c
// Or the exact opposite I don't remember
bool bad(Line a, Line b, Line c) {
    return (a.b - b.b) * (b.m - c.m) < (a.m - b.m) * (b.b - c.b);
}

struct CHT {
    vector<Line> lines;

    void insert(Line x) {
        while (lines.size() >= 2 and !bad(x, lines[lines.size() - 1], lines[lines.size() - 2])) {
            lines.pop_back();
        }
        lines.push_back(x);
    }

    ll query(ll x) {
        if (lines.empty()) return 0;

        ll l = 0, r = lines.size() - 1;
        while (r > l) {
            ll mid = l + (r - l) / 2;
            if (lines[mid].get(x) <= lines[mid + 1].get(x)) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return lines[l].get(x);
    }
};
