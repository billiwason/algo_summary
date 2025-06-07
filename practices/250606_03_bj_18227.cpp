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

////////////////////////////////////////////////////////////// code AREA

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




int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N , Root;
	cin >> N >> Root;

	iv2 graph(N+1);
	FanWickTree<int> FT(N);

	FOR(i, N-1)
	{
		int n1, n2;
		cin >> n1 >> n2;

		graph[n1].push_back(n2);
		graph[n2].push_back(n1);
	}

	iv tin(N+1);
	iv tout(N+1);
	iv level(N+1);

	function<void(int,int,int)> getOtt;
	int timer = 0;
	getOtt = [&] (int cur, int parent, int lv) -> void {
		tin[cur] = ++timer;
		level[cur] = lv;

		for(auto &n : graph[cur])
		{
			if(n == parent)
				continue;
			getOtt(n, cur, lv+1);
		}
		tout[cur] = timer;
	};
	getOtt(Root, -1, 1);

	int Q;
	cin >> Q;
	FOR(i, Q)
	{
		int op, city;
		cin >> op >> city;

		if(op == 1)
		{
			FT.update(tin[city], 1);
		}
		else
		{
			//cout << "level =" << level[city] << endl;
			ll ans = (ll)level[city] * FT.query(tin[city], tout[city]);
			cout << ans << endl;
		}
	}

	


    return 0;    
}