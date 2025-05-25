#include <limits.h>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <functional>
#include <cmath>
#include <stack>
#include <tuple>
#include <cassert>
#include <list>
#include <bitset>
#include <numeric>
#include <type_traits>
#include <iomanip>
#include <string.h>
#include <unordered_set>
 
using namespace std;
 
#define endl "\n"
 
typedef long long ll;
 
typedef pair<int,int> ip;
typedef vector<ip> ipv;
typedef vector<ipv> ipv2;

typedef vector<int> iv;
typedef vector<iv> iv2;
typedef vector<iv2> iv3;
typedef vector<iv3> iv4;

typedef vector<ll> llv;
typedef vector<llv> llv2;
typedef vector<llv2> llv3;
typedef vector<llv3> llv4;

typedef vector<double> dv;
typedef vector<dv> dv2;

#define INF_1E97 ((int)1e9+7)
#define INF_1E187 ((ll)1e18+7)
#define INF_1E127 ((ll)1e12+7)
 
#define CHECK_BIT_LL(X, I) ((X) & (1LL<<(I)))
#define BIT_INV_LL(X, I) (X) ^= (1LL<<(I))
 
#define BIT_SET_LL(X, I) (X) |= (1LL<<I)
#define BIT_CLEAR_LL(X, I) (X) &= ~(1LL<<I)
 
 
#define BOOL_INV(X) (x) ^= true
#define CHECK_BIT(X, I) ((X) & (1<<(I)))
#define BIT_INV(X, I) (X) ^= (1<<(I))
 
#define BIT_SET(X, I) (X) |= (1<<(I))
#define BIT_CLEAR(X, I) (X) &= ~(1<<(I))
 
 
// 우선 순위를 설정할 수있는 priority queue
/*
    auto cmp = [](int_pair& a, int_pair& b) {
        return a.second > b.second; // 오름차순 정렬
    };
 
    priority_queue<int_pair, vector<int_pair>, decltype(cmp)> q(cmp);
*/
 
// 소수점 좌표 지정 출력
/*
 
    cout << fixed;
    cout.precision(1);
    cout << abs(ans) << endl;
 
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace at_segtree {
 
    namespace internal {
     
    int ceil_pow2(int n) {
        int x = 0;
        while ((1U << x) < (unsigned int)(n)) x++;
        return x;
    }
     
    int bsf(unsigned int n) {
        return __builtin_ctz(n);
    }
     
    }  // namespace internal
     
    template <class S, S (*op)(S, S), S (*e)()> struct segtree {
      public:
        segtree() : segtree(0) {}
        segtree(int n) : segtree(std::vector<S>(n, e())) {}
        segtree(const std::vector<S>& v) : _n(int(v.size())) {
            log = internal::ceil_pow2(_n);
            size = 1 << log;
            d = std::vector<S>(2 * size, e());
            for (int i = 0; i < _n; i++) d[size + i] = v[i];
            for (int i = size - 1; i >= 1; i--) {
                update(i);
            }
        }
     
        void set(int p, S x) {
            assert(0 <= p && p < _n);
            p += size;
            d[p] = x;
            for (int i = 1; i <= log; i++) update(p >> i);
        }
     
        S get(int p) {
            assert(0 <= p && p < _n);
            return d[p + size];
        }
     
        S prod(int l, int r) {
            assert(0 <= l && l <= r && r <= _n);
            S sml = e(), smr = e();
            l += size;
            r += size;
     
            while (l < r) {
                if (l & 1) sml = op(sml, d[l++]);
                if (r & 1) smr = op(d[--r], smr);
                l >>= 1;
                r >>= 1;
            }
            return op(sml, smr);
        }
     
        S all_prod() { return d[1]; }
     
        template <bool (*f)(S)> int max_right(int l) {
            return max_right(l, [](S x) { return f(x); });
        }
        template <class F> int max_right(int l, F f) {
            assert(0 <= l && l <= _n);
            assert(f(e()));
            if (l == _n) return _n;
            l += size;
            S sm = e();
            do {
                while (l % 2 == 0) l >>= 1;
                if (!f(op(sm, d[l]))) {
                    while (l < size) {
                        l = (2 * l);
                        if (f(op(sm, d[l]))) {
                            sm = op(sm, d[l]);
                            l++;
                        }
                    }
                    return l - size;
                }
                sm = op(sm, d[l]);
                l++;
            } while ((l & -l) != l);
            return _n;
        }
     
        template <bool (*f)(S)> int min_left(int r) {
            return min_left(r, [](S x) { return f(x); });
        }
        template <class F> int min_left(int r, F f) {
            assert(0 <= r && r <= _n);
            assert(f(e()));
            if (r == 0) return 0;
            r += size;
            S sm = e();
            do {
                r--;
                while (r > 1 && (r % 2)) r >>= 1;
                if (!f(op(d[r], sm))) {
                    while (r < size) {
                        r = (2 * r + 1);
                        if (f(op(d[r], sm))) {
                            sm = op(d[r], sm);
                            r--;
                        }
                    }
                    return r + 1 - size;
                }
                sm = op(d[r], sm);
            } while ((r & -r) != r);
            return 0;
        }
     
      private:
        int _n, size, log;
        std::vector<S> d;
     
        void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    };
     
}



using namespace at_segtree;
 
int op(int a, int b) { return min(a, b); }
 
int e() { return INF_1E97; }
 

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    iv arr = { 111, 523, 20, 555 ,3 };
    segtree<int, op, e> seg(arr);
    
    // 시작 인덱스는 포함, 종료 인덱스는 미포함
    cout << seg.prod(0, 5) << endl;

    return 0;
}