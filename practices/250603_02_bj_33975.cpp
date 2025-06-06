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


int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;
	cin >> N;

	string S1, S2;
	cin >> S1 >> S2;

	N *= 2;

	iv RA, RB, UA, UB;

	FOR(i, N)
	{
		if(S1[i] == 'R')
			RA.push_back(i);
		else
			UA.push_back(i);
	}

	FOR(i, N)
	{
		if(S2[i] == 'R')
			RB.push_back(i);
		else
			UB.push_back(i);
	}
	ll ans = INF_1E187;

	auto getSubAns = [&] (iv &A, iv &B) -> ll
	{
		int sz = A.size();
		ll ans = A[0];
		for(int i = 1; i < sz ; i++)
		{
			if(A[i] <= B[i-1])
				continue;
			ans += A[i] - B[i-1];
		}
		ans += (N-1) - B[sz-1];
		return ans;
	};

	ll subAns = getSubAns(RA, RB);
	ans = min(ans , subAns);
	subAns = getSubAns(RB, RA);
	ans = min(ans , subAns);

	subAns = getSubAns(UA, UB);
	ans = min(ans , subAns);
	subAns = getSubAns(UB, UA);
	ans = min(ans , subAns);

	cout << ans << endl;
    return 0;    
}