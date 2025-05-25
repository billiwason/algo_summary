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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void solve()
{
    int N;
    cin >> N;

    iv order(N+1);

    vector<set<int>> indegree(N+1);

    for(int i = 1 ; i <= N ; i++)
    {
        cin >> order[i];
    }

    for(int i = 1 ; i <= N ; i++)
    {
        int cur = order[i];
        for(int j = i+1 ; j <= N ; j++)
        {
            int next = order[j];
            indegree[next].emplace(cur);
        }
    }

    int Q;
    cin >> Q;
    FOR(i, Q)
    {
        int a,b;
        cin >> a >> b;
        if(indegree[a].find(b) != indegree[a].end())
        {
            indegree[a].erase(b);
            indegree[b].emplace(a);
        }
        else
        {
            indegree[a].emplace(b);
            indegree[b].erase(a);
        }

    }

    queue<int> que;
    for(int i = 1 ; i <= N ; i++)
    {
        if(indegree[i].size() == 0)
            que.push(i);
    }
    if(que.size() != 1)
    {
        cout << "IMPOSSIBLE" << endl;
        return;
    }


    iv2 teamLoc(N+1);


    for(int i = 1; i <= N ; i++)
    {
        for(auto &it : indegree[i])
        {
            teamLoc[it].push_back(i);
        }
    }

    iv ans;
    while(!que.empty())
    {
        auto top = que.front();
        que.pop();
        ans.push_back(top);

        for(auto &n : teamLoc[top])
        {
            indegree[n].erase(top);
            if(indegree[n].size() == 0)
            {
                que.push(n);
            }
        }
        if(que.size() > 1)
        {   
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    }
    if((int)ans.size() != N)
    {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    for(auto &a : ans)
    {
        cout << a << " ";
    }
    cout << endl;
}


int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
           
    int T;
    cin >> T;
    while(T--)
    {
        solve();
    }
    
    return 0;
}