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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// union find
// 유니온 파인드 클래스
// UnionFind uf(N+1) 로 생성해야 한다.
class UnionFind
{
	iv m_parent;
	iv m_rank;
    iv m_size;
 
public:
	UnionFind(int nrItem)
	{
		m_parent.resize(nrItem, 0);
		m_rank.resize(nrItem, 1);
        m_size.resize(nrItem, 1);
 
		for (int i = 0; i < nrItem; i++)
			m_parent[i] = i;
	}
	int find(int x) {
		if (x == m_parent[x])
			return x;
		else
			return m_parent[x] = find(m_parent[x]);
	}
	void uni(int x, int y) {
		//printf("UNI : %d %d \n", x, y);

		x = find(x);
		y = find(y);
		if (x == y)
			return;

        int szX = m_size[x];
        int szY = m_size[y];
		if (m_rank[x] < m_rank[y])
			swap(x, y);
		m_parent[y] = x;
 
		if (m_rank[x] == m_rank[y]) {
			m_rank[x] = m_rank[y] + 1;
		}
        m_size[x] = m_size[y] = szX + szY;
	}
    void uni_userdefine(int x, int y)
    {
        x = find(x);
		y = find(y);
		if (x == y)
			return;
        m_parent[x] = y;
    }
    int getSize(int i)
    {
        return m_size[find(i)];
    }
};
 

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N , Q;
	cin >> N >> Q;

	UnionFind UF(N+1);

	FOR(i, Q)
	{
		int op;
		cin >> op;
		int a, b;
		cin >> a >> b;
		if(op == 0)
		{
			UF.uni(a,b);
		}
		else
		{
			if(UF.find(a) == UF.find(b))
			{
				cout << "YES" << endl;
			}
			else
			{
				cout << "NO" << endl;
			}
		}
	}
    
    return 0;
}