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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ll getPowMod(ll base, ll po, const ll mod)
{
<<<<<<<< HEAD:practices/algo_history/binary_coefficient/bj_11402_Lucas.cpp
	if (po == 0) return 1;
	if (po % 2 > 0)
        return (getPowMod(base, po - 1, mod) * base) % mod;
	ll half = getPowMod(base, po / 2, mod) % mod;
	return (half * half) % mod;
}
========
    int N;
    cin >> N;
    int sqrt = (int)cbrt(N);

    auto getSubAns = [&] (int s1, int s2, int remain) -> int {
        //cout << "s1,s2=" << s1 << "," << s2 << ", remain =" << remain << endl; 
        if(remain == 0)
            return 0;
        int ans = INF_1E97;
        for(int i = 1; i <= s2 ; i++)
        {
            int x = i;
            int y = remain / x;
            if(remain % x > 0)
            {
                y++;
            }
            if(max(x,y) > s2 || min(x,y) > s1)
                continue;
            if(y == 0)
                break;
            ans = min(ans , (x+y) * 2);
        }
        return ans;
    };
>>>>>>>> 37ec6b9d02d5068dc92af6051bb2583f94191a09:practices/bj_34004.cpp


    int ans = 0;
    int remain = 0;
    if(N < (sqrt +1) * pow(sqrt , 2))
    {
        //cout << "case1" << endl;
        ans = sqrt * sqrt * 6;
        remain = N - pow(sqrt , 3);

        ans += getSubAns(sqrt, sqrt, remain);
    }
    else if(N < sqrt * pow(sqrt+1, 2))
    {
        //cout << "case2" << endl;
        ans = sqrt * (sqrt +1) * 4 + pow(sqrt, 2) * 2;
        remain = N - (sqrt +1) * pow(sqrt , 2);
        ans += getSubAns(sqrt, sqrt+1, remain);
    }
    else
    {
        //cout << "case3" << endl;
        ans = sqrt * (sqrt +1) * 4 + pow(sqrt+1, 2) * 2;
        remain = N - sqrt * pow(sqrt+1, 2);
        ans += getSubAns(sqrt+1, sqrt+1, remain);
    }
    cout << ans << endl;
}

int main() {

<<<<<<<< HEAD:practices/algo_history/binary_coefficient/bj_11402_Lucas.cpp
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
           
    ll N, K, mod;
    cin >> N >> K >> mod;

    llv factTable(mod+1);

    for(ll i = 0 ; i <= mod ; i++)
========
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tc;
    cin >> tc;
    FOR(i, tc)
>>>>>>>> 37ec6b9d02d5068dc92af6051bb2583f94191a09:practices/bj_34004.cpp
    {
        if(i <= 1)
            factTable[i] = 1;

        else
        {
            factTable[i] = 1LL * factTable[i-1] * i;
            factTable[i] %= mod;
        }
    }
<<<<<<<< HEAD:practices/algo_history/binary_coefficient/bj_11402_Lucas.cpp

    ll ans = 1;

    auto getBinaryCoeff = [&] (ll n, ll k) -> ll {
        ll a = factTable[n];
        ll b = (factTable[n-k] * factTable[k]) % mod;

        ll ans = (a * getPowMod(b, mod-2, mod)) % mod;
        return ans;
    };


    while(N > 0 || K > 0)
    {
        ll remain_N = N % mod;
        ll remain_K = K % mod;
        
        N /= mod;
        K /= mod;

        if(remain_N == remain_K)
            continue;
        
        if(remain_N < remain_K)
        {
            ans = 0;
            break;
        }
        ans *= getBinaryCoeff(remain_N, remain_K);

        ans %= mod;
    }
    cout << ans << endl;



    return 0;
========
>>>>>>>> 37ec6b9d02d5068dc92af6051bb2583f94191a09:practices/bj_34004.cpp
}