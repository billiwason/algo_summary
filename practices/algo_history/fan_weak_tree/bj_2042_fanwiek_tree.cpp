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

#define FOR(X, Y) for(int X = 0 ; X < (Y) ; X++)
#define FOR2(X, Y, Z) for(int X = (Y); X < (Z) ; X++)
 
 
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

//팬웍트리
// 펜윅트리를 이용하여 구간쿠리를 수행함. FW Tree 클래스 성질은 아래와 같다.
// index 0 은 미사용. 1부터~ N 까지 쿼리함.
// 쿼리시 S, E 둘다 포함됨.
template <typename T>
class FanWorkTree
{
	vector<T> tree_;
public:
	FanWorkTree(T n) : tree_(n+1) {}
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
 


int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N , Q1, Q2;
	cin >> N >> Q1 >> Q2;

	FanWorkTree<ll> FT(N);

	llv arr(N+1);

	for(int i = 1 ; i <= N ; i++)
	{
		cin >> arr[i];
		FT.update(i, arr[i]);
	}

	int Q = Q1 + Q2;

	FOR(i, Q)
	{
		int op;
		cin >> op;
		if(op == 1)
		{
			int idx;
			ll newVal;
			cin >> idx >> newVal;
			
			ll diff = newVal - arr[idx];
			FT.update(idx, diff);
			arr[idx] = newVal;
		}
		else
		{
			int s, e;
			cin >> s >> e;
			ll ans = FT.query(s, e);
			cout << ans << endl;
		}
	}
    
    return 0;
}