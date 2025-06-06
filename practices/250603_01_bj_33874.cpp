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

    llv DP_FACT(N+1, 1);
    for(int i = 2 ; i <= N ; i++)
    {
        ll ans = (DP_FACT[i-1] * i) % INF_1E97;
        DP_FACT[i] = ans;
    }

    map<ll,ll> ans;

    auto updateSubAns = [&] (int n1, int k1 , int n2, int k2, int cnt) -> void {
        if(n1 < 0 || n2 < 0 || k1 < 0 || k2 < 0)
            return ;

        ll subAns = 0;
        ll a = DP_FACT[n1];
        ll b = (DP_FACT[n1-k1] * DP_FACT[k1]) % INF_1E97;

        ll c = DP_FACT[n2];
        ll d = (DP_FACT[n2-k2] * DP_FACT[k2]) % INF_1E97;

        ll child = (((a * d) % INF_1E97) - ((b * c) % INF_1E97));
        if(child < 0)
        {
            child += INF_1E97;
        }
        ll parent = (b * d) % INF_1E97;

        subAns = child * getPowMod(parent, INF_1E97-2, INF_1E97);
        subAns %= INF_1E97;

        ans[subAns] += cnt;
    };

    if(N <= 10)
    {

        if(N % 2 == 0) // N 번째 줄이 짝수 ( n-1 C 0 , n-1 C 1 .... n-1 C n-1 )
        {
            int mid = N /2 ;
            updateSubAns(N-1, mid-2, N-1, mid-3, 2); // n1k1 > n2k2  2개
            updateSubAns(N-1, mid-1, N-1, mid-2, 2); // 2개
            updateSubAns(N-1, mid-2, N-2, mid-3, 2); // 2개
            updateSubAns(N-1, mid-2, N-2, mid-2, 2); // 2개
            updateSubAns(N-1, mid-1, N-2, mid-2, 2); // 2개
            updateSubAns(N-1, mid-1, N-2, mid-1, 2); // 2개 
            ans[0]++;

        }
        else
        {
            int mid = N /2 ;
            updateSubAns(N-1, mid-1, N-1, mid-2, 2);
            updateSubAns(N-1, mid, N-1, mid-1, 2);
            updateSubAns(N-1, mid-1, N-2, mid-2, 2);
            updateSubAns(N-1, mid-1, N-2, mid-1, 2);
            updateSubAns(N-1, mid, N-2, mid-1, 2);
        }
    }
    else
    {
        int mid = N /2 ;

        if(N %2 == 1)
            updateSubAns(N-1, mid, N-2, mid, 4);
        else
            updateSubAns(N-1, mid, N-2, mid, 2);
    
    }
    cout << ans.rbegin()->first << " " << ans.rbegin()->second << endl;
    
}