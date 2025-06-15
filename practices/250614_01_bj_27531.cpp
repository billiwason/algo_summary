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

typedef map<int,int> intmap;
typedef map<ll, ll> llmap;

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

#define FOR(X, Y) for(int X = 0 ; X < (Y) ; X++)
#define FOR2(X, Y, Z) for(int X = (Y); X < (Z) ; X++)


template <typename T>
void printDPTable(string prefix , vector<T> dp)
{
    cout << prefix << endl;
    for(int i = 0 ; i < (int)dp.size() ; i++)
    {
        cout << "DP " << i << "] =" << dp[i] << endl;
    }
}
 
 
template <typename T>
void printDPTable2D(string prefix , vector<vector<T>> dp , T lim = INF_1E97)
{
    cout << prefix << endl;
    for(int r = 0 ; r < (int)dp.size() ; r++)
    {
        for(int c = 0 ; c < (int)dp[r].size() ; c++)
        {
            if( dp[r][c] >= lim)
                cout << "DP " << r << "," << c << "] =" << "INF" << " | ";
            else
                cout << "DP " << r << "," << c << "] =" << dp[r][c] << " | ";
        }
        cout << endl;
    }
}
 


vector<ll> getPrimeNumber(ll limit)
{
	vector<ll> numList(limit + 1, 1);
	numList[0] = 0;
	numList[1] = 0;
 
	for (int i = 2; i < limit + 1; i++)
	{
		if (numList[i])
		{
			for (ll m = 2; i * m < limit + 1; m++)
			{
				numList[i * m] = 0;
			}
		}
	}
	vector<ll> result;
	FOR(i, (int)numList.size())
	{
		if (numList[i]) {
			result.push_back(i);
		}
	}
	return result;
}
 
 
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

ll getPowMod(ll base, ll po, const ll mod)
{
	if (po == 0) return 1;
	if (po % 2 > 0)
        return (getPowMod(base, po - 1, mod) * base) % mod;
	ll half = getPowMod(base, po / 2, mod) % mod;
	return (half * half) % mod;
}

//팬웍트리
// 펜윅트리를 이용하여 구간쿠리를 수행함. FW Tree 클래스 성질은 아래와 같다.
// index 0 은 미사용. 1부터~ N 까지 쿼리함.
// 쿼리시 S, E 둘다 포함됨.
template <typename T>
class FanWickTree
{
	vector<T> tree_;
public:
	FanWickTree(T n) : tree_(n+1) {}
	T sum(T x) {
		T ans = 0;
		for (T i = x; i > 0; i -= i & -i) {
			ans += tree_[i];
		}
		return ans;
	}
	void update(T x, T diff) {
		for (T i = x; i < (T)tree_.size(); i += i & -i) {
			tree_[i] += diff;
		}
	}
    T query(T s, T e) {
        return sum(e) - sum(s-1);
    }
};

namespace myLazySegment {
	namespace internal {
	// @return same with std::bit::bit_ceil
	unsigned int bit_ceil(unsigned int n) {
		unsigned int x = 1;
		while (x < (unsigned int)(n)) x *= 2;
		return x;
	}
	 
	// @param n `1 <= n`
	// @return same with std::bit::countr_zero
	int countr_zero(unsigned int n) {
		return __builtin_ctz(n);
	}
	 
	// @param n `1 <= n`
	// @return same with std::bit::countr_zero
	constexpr int countr_zero_constexpr(unsigned int n) {
		int x = 0;
		while (!(n & (1 << x))) x++;
		return x;
	}
	}
	 
	template <class S,
			  S (*op)(S, S),
			  S (*e)(),
			  class F,
			  S (*mapping)(F, S),
			  F (*composition)(F, F),
			  F (*id)()>
	struct lazy_segtree {
	 
	  public:
		lazy_segtree() : lazy_segtree(0) {}
		explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
		explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
			size = (int)internal::bit_ceil((unsigned int)(_n));
			log = internal::countr_zero((unsigned int)size);
			d = std::vector<S>(2 * size, e());
			lz = std::vector<F>(size, id());
			for (int i = 0; i < _n; i++) d[size + i] = v[i];
			for (int i = size - 1; i >= 1; i--) {
				update(i);
			}
		}
	 
		void set(int p, S x) {
			assert(0 <= p && p < _n);
			p += size;
			for (int i = log; i >= 1; i--) push(p >> i);
			d[p] = x;
			for (int i = 1; i <= log; i++) update(p >> i);
		}
	 
		S get(int p) {
			assert(0 <= p && p < _n);
			p += size;
			for (int i = log; i >= 1; i--) push(p >> i);
			return d[p];
		}
	 
		S prod(int l, int r) {
			assert(0 <= l && l <= r && r <= _n);
			if (l == r) return e();
	 
			l += size;
			r += size;
	 
			for (int i = log; i >= 1; i--) {
				if (((l >> i) << i) != l) push(l >> i);
				if (((r >> i) << i) != r) push((r - 1) >> i);
			}
	 
			S sml = e(), smr = e();
			while (l < r) {
				if (l & 1) sml = op(sml, d[l++]);
				if (r & 1) smr = op(d[--r], smr);
				l >>= 1;
				r >>= 1;
			}
	 
			return op(sml, smr);
		}
	 
		S all_prod() { return d[1]; }
	 
		void apply(int p, F f) {
			assert(0 <= p && p < _n);
			p += size;
			for (int i = log; i >= 1; i--) push(p >> i);
			d[p] = mapping(f, d[p]);
			for (int i = 1; i <= log; i++) update(p >> i);
		}
		void apply(int l, int r, F f) {
			assert(0 <= l && l <= r && r <= _n);
			if (l == r) return;
	 
			l += size;
			r += size;
	 
			for (int i = log; i >= 1; i--) {
				if (((l >> i) << i) != l) push(l >> i);
				if (((r >> i) << i) != r) push((r - 1) >> i);
			}
	 
			{
				int l2 = l, r2 = r;
				while (l < r) {
					if (l & 1) all_apply(l++, f);
					if (r & 1) all_apply(--r, f);
					l >>= 1;
					r >>= 1;
				}
				l = l2;
				r = r2;
			}
	 
			for (int i = 1; i <= log; i++) {
				if (((l >> i) << i) != l) update(l >> i);
				if (((r >> i) << i) != r) update((r - 1) >> i);
			}
		}
	 
		template <bool (*g)(S)> int max_right(int l) {
			return max_right(l, [](S x) { return g(x); });
		}
		template <class G> int max_right(int l, G g) {
			assert(0 <= l && l <= _n);
			assert(g(e()));
			if (l == _n) return _n;
			l += size;
			for (int i = log; i >= 1; i--) push(l >> i);
			S sm = e();
			do {
				while (l % 2 == 0) l >>= 1;
				if (!g(op(sm, d[l]))) {
					while (l < size) {
						push(l);
						l = (2 * l);
						if (g(op(sm, d[l]))) {
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
	 
		template <bool (*g)(S)> int min_left(int r) {
			return min_left(r, [](S x) { return g(x); });
		}
		template <class G> int min_left(int r, G g) {
			assert(0 <= r && r <= _n);
			assert(g(e()));
			if (r == 0) return 0;
			r += size;
			for (int i = log; i >= 1; i--) push((r - 1) >> i);
			S sm = e();
			do {
				r--;
				while (r > 1 && (r % 2)) r >>= 1;
				if (!g(op(d[r], sm))) {
					while (r < size) {
						push(r);
						r = (2 * r + 1);
						if (g(op(d[r], sm))) {
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
		std::vector<F> lz;
	 
		void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
		void all_apply(int k, F f) {
			d[k] = mapping(f, d[k]);
			if (k < size) lz[k] = composition(f, lz[k]);
		}
		void push(int k) {
			all_apply(2 * k, lz[k]);
			all_apply(2 * k + 1, lz[k]);
			lz[k] = id();
		}
	};
	 
}
	 	 
// using namespace myLazySegment;
// struct S {
// 	ll a;
// 	ll size;
// };
	
// struct F {
// 	ll a, b;
// };
	
// S op(S l, S r) { return S{l.a + r.a, l.size + r.size}; }
// S e() { return S{0, 0}; }
// S mapping(F l, S r) { return S{r.a * l.a + r.size * l.b, r.size}; }
// F composition(F l, F r) { return F{r.a * l.a, r.b * l.a + l.b}; }
// F id() { return F{1, 0}; }
// lazy_segtree<S, op, e, F, mapping, composition, id> seg(arr);



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

/*
===========================================
 🔷🔷🔷 Lazy Segment Tree Example 🔷🔷🔷
===========================================
*/

// using namespace myLazySegment;
// struct S {
// 	ll a;
// 	ll size;
// };
	
// struct F {
// 	ll a, b;
// };
	
// S op(S l, S r) { return S{l.a + r.a, l.size + r.size}; }
// S e() { return S{0, 0}; }
// S mapping(F l, S r) { return S{r.a * l.a + r.size * l.b, r.size}; }
// F composition(F l, F r) { return F{r.a * l.a, r.b * l.a + l.b}; }
// F id() { return F{1, 0}; }
// lazy_segtree<S, op, e, F, mapping, composition, id> seg(arr);


/*
===========================================
 🔷🔷🔷 Segment Tree Example 🔷🔷🔷
===========================================
*/

// using namespace at_segtree;
// ll op(ll a, ll b) { return max(a, b); } 
// ll e() { return 0; }
//
// iv arr = { 111, 523, 20, 555 ,3 };
// segtree<int, op, e> seg(arr);



namespace atcoder_dsu {

	struct dsu {
	  public:
		dsu() : _n(0) {}
		dsu(int n) : _n(n), parent_or_size(n, -1) {}
	
		int merge(int a, int b) {
			assert(0 <= a && a < _n);
			assert(0 <= b && b < _n);
			int x = leader(a), y = leader(b);
			if (x == y) return x;
			if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
			parent_or_size[x] += parent_or_size[y];
			parent_or_size[y] = x;
			return x;
		}
	
		bool same(int a, int b) {
			assert(0 <= a && a < _n);
			assert(0 <= b && b < _n);
			return leader(a) == leader(b);
		}
	
		int leader(int a) {
			assert(0 <= a && a < _n);
			if (parent_or_size[a] < 0) return a;
			return parent_or_size[a] = leader(parent_or_size[a]);
		}
	
		int size(int a) {
			assert(0 <= a && a < _n);
			return -parent_or_size[leader(a)];
		}
	
		std::vector<std::vector<int>> groups() {
			std::vector<int> leader_buf(_n), group_size(_n);
			for (int i = 0; i < _n; i++) {
				leader_buf[i] = leader(i);
				group_size[leader_buf[i]]++;
			}
			std::vector<std::vector<int>> result(_n);
			for (int i = 0; i < _n; i++) {
				result[i].reserve(group_size[i]);
			}
			for (int i = 0; i < _n; i++) {
				result[leader_buf[i]].push_back(i);
			}
			result.erase(
				std::remove_if(result.begin(), result.end(),
							   [&](const std::vector<int>& v) { return v.empty(); }),
				result.end());
			return result;
		}
	
	  private:
		int _n;
		std::vector<int> parent_or_size;
	};
	
}  // namespace atcoder

/*
===========================================
 🔷🔷🔷 Union Find Example 🔷🔷🔷
===========================================
*/

// using namespace atcoder_dsu;
// dsu UF(N+1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    int N;
    cin >> N;

    iv arr(N+1);
    iv wei(N+1);
    iv visit(N+1);

    int ans = 0;

    FOR(i, N)
    {
        int a,b, w;
        cin >> a >> b >> w;
        arr[a] = b;
        wei[a] = w;

        if(a == b)
        {
            ans += w;
            visit[a] = true;
        }
    }

    auto getSubAns = [](iv &array) -> int {
        int sz = array.size();
        iv2 DP(sz, iv(2, INF_1E97));

        // case 1 : 마지막  egde 가 미포함
        // 첫번째 edge 는 무조건 포함되어야 함.
        // 0 : i 번째 edge 가 미포함
        // 1 : i 번째 edge 가 포함.
        // 마지막 edge 가 미포함이므로 첫번재 edge 가 미포함인 경우는 성립안됨.
        DP[0][0] = INF_1E97;
        DP[0][1] = array[0];

        for(int i = 1 ; i < sz ; i++)
        {
            // 현재 Edge 가 미포함이면 이전 Edge 는 반드시 포함되어야 함.
            DP[i][0] = DP[i-1][1];
            // 현재 Edge 가 포함이면 이전  Edge 는 포함될 수도 있고 안될 수 도 있다.
            DP[i][1] = min(DP[i-1][0] , DP[i-1][1]) + array[i]; 
        }
        // 마지막 Edge 가 미포함이므로 case1 의 최소값은 DP[sz-1][0] 이다.
        int ans1 = DP[sz-1][0];

        // case2 : 마지막 edge 가 포함인 경우
        DP[0][0] = 0;
        DP[0][1] = array[0];

        for(int i = 1 ; i < sz ; i++)
        {
            // 현재 Edge 가 미포함이면 이전 Edge 는 반드시 포함되어야 함.
            DP[i][0] = DP[i-1][1];
            // 현재 Edge 가 포함이면 이전  Edge 는 포함될 수도 있고 안될 수 도 있다.
            DP[i][1] = min(DP[i-1][0] , DP[i-1][1]) + array[i]; 
        }
        // 마지막 edge 가 포함되어야 하기 때문에 case2 의 최소값은 DP[sz-1][1] 이다.
        int ans2 =  DP[sz-1][1];

        return  min(ans1, ans2) ;
    };

    while(1)
    {
        int start = -1;
        for(int i = 1 ; i <= N ; i++)
        {
            if(visit[i] == 0)
            {
                start = i;
                visit[i] = 1;
                break;
            }
        }
        if(start == -1)
            break;

        int cur = start;
        iv edges;
        do
        {
            cur = arr[cur];
            edges.push_back(wei[cur]);
            visit[cur] = 1;
        } while (cur != start);

        int subAns = getSubAns(edges);
        ans += subAns;
    }
    cout << ans << endl;

    return 0;    
}