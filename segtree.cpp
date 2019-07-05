typedef long long int ll;
#define MAX 1000000
namespace seg {
    ll st[4*MAX], lazy[4*MAX];
    int n, *v;

    ll build(int ind=1, int l=0, int r=n-1) {
        lazy[ind] = 0;

        if(l == r) {
            st[ind] = v[l];
            return st[ind];
        }
        int m = (l+r)/2;
        ll a1 = build(2*ind, l, m);
        ll a2 = build(2*ind+1, m+1, r);

        st[ind] = a1 + a2;
        return st[ind];
    }

    void build(int nn, int* vv) {
        n = nn;
        v = vv;
        build();
    }
    void propagation(int ind, int l, int r) {
        st[ind] += lazy[ind]*(1 + r-l);
        if(l != r) {
            lazy[2*ind] += lazy[ind];
            lazy[2*ind+1] += lazy[ind];
        }
        lazy[ind] = 0;
    }
    ll query(int a, int b, int ind=1, int l=0, int r=n-1) {
        propagation(ind, l, r);
        if(a <= l and r <= b) {
            return st[ind];
        }
        else if(b < l)
            return 0;
        else if(a > r)
            return 0;
        else {
            int m = (l+r)/2;
            int a1 = query(a, b, 2*ind, l, m);
            int a2 = query(a, b, 2*ind+1, m+1, r);
            st[ind] = a1 + a2;
            return st[ind];
        }
    }
    ll update(int a, int b, int val, int ind=1, int l=0, int r=n-1) {
        propagation(ind, l, r);
        if(b < l)
            return st[ind];
        if(a > r)
            return st[ind];

        if(a <= l and b >= r) {
            lazy[ind] += val;
            propagation(ind, l, r);
            return seg[ind];
        }
        int m = (l+r)/2;
        int a1 = update(a, b, val, 2*ind, l, m);
        int a2 = update(a, b, val, 2*ind+1, m+1, r);
        seg[ind] = a1+a2;
        return seg[ind];
    }
};
