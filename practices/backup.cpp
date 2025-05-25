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
 
typedef unsigned long long ull;
typedef long long ll;
 
typedef pair<int,int> int_pair;
typedef pair<ll,ll> ll_pair;
 
typedef vector<int> int_vector;
 
typedef vector<bool> bool_vector;
 
typedef vector<ll> ll_vector;
 
typedef vector<vector<ll>> ll_vector_2d;
 
typedef vector<vector<int>> int_vector_2d;
 
typedef vector<vector<bool>> bool_vector_2d;
 
typedef vector<vector<vector<int>>> int_vector_3d;
 
 
typedef vector<pair<int, int>> int_pair_vector;
 
typedef vector<vector<pair<int, int>>> int_pair_vector_2d;
 
typedef vector<double> double_vector;
typedef vector<double_vector> double_vector_2d;
 
typedef map<int,int> int_map;
typedef map<ull,ull> ull_map;
typedef map<ll,ll> ll_map;
 
typedef vector<string> str_vector;
 
typedef vector<pair<ll,ll>> ll_pair_vector;
 
#define FOR(X, Y) for(int X = 0 ; X < (Y) ; X++)
#define FOR2(X, Y, Z) for(int X = (Y); X < (Z) ; X++)

typedef vector<ll_vector_2d> ll_vector_3d;
typedef vector<char> char_vector;
typedef vector<char_vector> char_vector_2d;
typedef vector<char_vector_2d> char_vector_3d;


typedef int_vector      iv;
typedef int_vector_2d   iv2;
typedef int_vector_3d   iv3;
typedef vector<iv3>     iv4;
typedef int_pair        ip;
typedef int_pair_vector ipv;
typedef vector<ipv>     ipv2;
typedef vector<ipv2>    ipv3;
typedef vector<ipv3>    ipv4;
 
typedef ll_vector               llv;
typedef ll_vector_2d            llv2;
typedef ll_vector_3d            llv3;
typedef vector<ll_vector_3d>    llv4;
typedef vector<ll_pair>         llpv;
typedef vector<llpv>            llpv2;
typedef ll_pair                 llp;
 
typedef queue<int>  iq;
typedef queue<ll>   llq;
typedef queue<int_pair> ipq;
typedef queue<ll_pair> llpq;
 
typedef vector<bool>    bv;
typedef vector<string>  sv;
 
typedef map<int,int> imp;
typedef map<ll,ll> llmp;

typedef vector<float> fv;
typedef vector<fv> fv2;
 
 
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
 
 
 
// 크루스칼 ( 최소 신장 (스패닝) 트리 )
class Kruskal
{
	struct Edge
	{
		int n1;
		int n2;
		int weight;
		bool operator < (const Edge& other) const {
			return weight < other.weight;
		}
	};
 
	UnionFind m_uFind;
	vector<Edge> m_EdgeList;
 
	int unionCnt = 0;
 
public:
	Kruskal(int nrNode) : m_uFind(nrNode) {}
	void AddEdge(int& n1, int& n2, int& w)
	{
		m_EdgeList.push_back(Edge{ n1,n2, w });
	}
	int getResult()
	{
		sort(m_EdgeList.begin(), m_EdgeList.end());
		int result = 0;
		for (auto& e : m_EdgeList)
		{
			if (m_uFind.find(e.n1) != m_uFind.find(e.n2))
			{
				m_uFind.uni(e.n1, e.n2);
				result += e.weight;
				unionCnt++;
			}
		}
		return result;
	}
	int getUnionCnt()
	{
		return unionCnt;
	}
 
};
 
template <typename T>
T getPow(T base, T po)
{
	if (po == 0) return 1;
	if (po % 2 > 0)
        return (getPow(base, po - 1) * base);
	T half = getPow(base, po / 2);
	return (half * half);
}
 
 
// 가장 증가하는 긴 부분 수열 찾기
class FindLongestSubArray
{
    int_vector nList_;
public:
    void add_array(int n)
    {
        nList_.push_back(n);
    }
 
    int findClosestMinIndex(int_vector &dp, int left, int right, int target) {
        int closestMin = INT_MAX;
        int closestMinIndex = 0;
 
        while (left <= right) {
            int mid = left + (right - left) / 2;
 
            if (dp[mid] < target) {
                if(target - dp[mid] < closestMin)
                {
                    closestMin = target - dp[mid];
                    closestMinIndex = mid;
                }
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
 
        return closestMinIndex;
    }
 
 
    int findAns()
    {
        int_vector dp(nList_.size()+1, 0);
        dp[1] = nList_[0];
 
        int curLen = 1;
 
        for(int i = 1 ; i < (int)nList_.size() ; i++)
        {
            if(nList_[i] > dp[curLen])
            {
                dp[curLen+1] = nList_[i];
                curLen++;
            }
            else
            {
                int cloestMinIndex = findClosestMinIndex(dp, 1, curLen, nList_[i]);
                dp[cloestMinIndex +1] = min(dp[cloestMinIndex +1], nList_[i]);
            }
        }
        return curLen++;
    }
 
};
 
// 유클리드 호제법을 이용한 최대 공약수 구하기
 
template <typename T>
T gcd(T a, T b) {
    //cout << "GCD = " << a << " " << b << endl;
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}
 
 
#define COUT_FOUR(A,B,C,D) cout << A << " , " << B << " , " << C << " , " << D << endl;
#define COUT_THREE(A,B,C) cout << A << " , " << B << " , " << C << endl;
#define COUT_TWO(A,B,C) cout << A << " , " << B << endl;

 
 
class TopologySort
{
	int m_nodes;
	int_vector_2d m_edges;
	int_vector m_indegreesInfo;
public:
	TopologySort(int nrNode) {
		m_nodes = nrNode;
		m_edges.resize(m_nodes, vector<int>());
		m_indegreesInfo.resize(nrNode, 0);
	}
	void addEdge(int& s, int& d)
	{
        //cout << "src = " << s << ", d = " << d << endl;
		m_edges[s].push_back(d);
		m_indegreesInfo[d]++;
	}
 
	int_vector getSortedOrder()
	{
        // 위상정렬 불가 -> 사이클이 있음
        // 사이클이 있으면 모든 노드를 순회하기 전에 Q 가 비워짐.
		queue<int> que;
		for (int i = 1; i < m_nodes; i++)
		{
			if (m_indegreesInfo[i] == 0)
			{
				que.push(i);
			}
		}
        int_vector ans;
		while (!que.empty())
		{
			int q = que.front();
            ans.push_back(q);
 
			for (auto& c : m_edges[q])
			{
				if (--m_indegreesInfo[c] == 0)
				{
					que.push(c);
				}
			}
			que.pop();
		}
        return ans;
	}
};
 
 
/*
위상정렬 사용 예제
int main()
{
	int nrWork;
	scanf("%d", &nrWork);
	TopologySort ts(nrWork + 1);
 
	int w, n, tmp;
	for (int i = 1; i <= nrWork; i++)
	{
		scanf("%d", &w);
		ts.setWeight(i, w);
		scanf("%d", &n);
 
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &tmp);
			ts.addEdge(tmp, i);
		}
	}
	printf("%d", ts.getMaxWeight());
}
*/
 
 
// n 개에서 s 개의 순열을 고르는 문제
void IteratePermutation(int n , int s)
{
    int_vector v;
    FOR(i,n)
    {
        v.push_back(i);
    }
    do {
        // do something
        FOR(i, s)
        {
            cout << v[i] << " ";
        }
        cout << endl;
 
    }while(next_permutation(v.begin(), v.end()));
 
}
 
 
// 이진 탐색 함수
int binarySearch(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
 
    while (low <= high) {
        int mid = low + (high - low) / 2;
 
        if (arr[mid] == target)
            return mid;
 
        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
 
    return -1;  // 찾지 못한 경우
}
/*
int main() {
    std::vector<int> arr = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int target = 23;
 
    int index = binarySearch(arr, target);
 
    if (index != -1)
        std::cout << "Element found at index: " << index << std::endl;
    else
        std::cout << "Element not found" << std::endl;
 
    return 0;
}
*/
 
 
// 타겟보다 큰 가장 작은 값 탐색 함수
int findSmallestGreaterThanTarget(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    int result = -1;  // 초기화된 값으로 설정
 
    while (low <= high) {
        int mid = low + (high - low) / 2;
 
        if (arr[mid] > target) {
            result = arr[mid];  // 타겟보다 큰 값 중에서 가장 작은 값을 저장
            high = mid - 1;     // 더 작은 값이 있을 수 있으므로 범위를 왼쪽으로 좁힘
        } else {
            low = mid + 1;      // 타겟보다 작거나 같은 값이므로 범위를 오른쪽으로 좁힘
        }
    }
 
    return result;
}
 
/*
int main() {
    std::vector<int> arr = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int target = 20;
 
    int result = findSmallestGreaterThanTarget(arr, target);
 
    if (result != -1)
        std::cout << "Smallest element greater than target: " << result << std::endl;
    else
        std::cout << "No element greater than target" << std::endl;
 
    return 0;
}
*/
 
 
 
 
 
// 가장 가까운 공통 조상 찾는 문제
class Lca
{
	int_vector_2d p;
	int_vector_2d edge;
	int_vector tin, tout;
	int timer;
	int log;
public:
	Lca(int nrNode) : edge(nrNode + 1), tin(nrNode +1), tout(nrNode+1), timer(0)
	{
		for (log = 1; (1 << log) <= nrNode; log++);
		log -= 1;
 
		p.resize(nrNode + 1, vector<int>(log+1, 0));
	}
	void addEdge(int& n1, int& n2)
	{
		edge[n1].push_back(n2);
		edge[n2].push_back(n1);
	}
	void dfs(int v, int parent) {
		tin[v] = ++timer;
		p[v][0] = parent;
		for (int i = 1; i <= log; i++)
		{
			p[v][i] = p[p[v][i - 1]][i - 1];
		}
		for (int& to : edge[v]) {
			if (to != parent) {
				dfs(to, v);
			}
		}
		tout[v] = ++timer;
	}
 
	int getLca(int u, int v)
	{
		if (upper(u, v)) return u;
		if (upper(v, u)) return v;
 
		for (int i = log; i >= 0; i--)
		{
			if (!upper(p[u][i], v))
			{
				u = p[u][i];
 
			}
		}
		return p[u][0];
	}
 
private:
	bool upper(int u, int v)
	{
		return (tin[u] <= tin[v] && tout[u] >= tout[v]);
	}
};
 
// 출력량이 많을때에는 endl 보다는 "\n" 이 많이 빠르다.
// 이에 따라 시간 초과가 나기도 하고 안나기도 한다.
 
 
// LCA 예제
/*
int main()
{
 
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
 
    int nrNode;
    cin >> nrNode;
 
    Lca lca(nrNode);
 
    FOR(i, nrNode-1)
    {
        int n1, n2;
        cin >> n1 >> n2;
 
        lca.addEdge(n1,n2);
    }
    lca.dfs(1,1);
    int cnt;
    cin >> cnt;
 
    FOR(i, cnt)
    {
        int n1, n2;
        cin >> n1 >> n2;
        int ans = lca.getLca(n1,n2);
 
        cout << ans << "\n";
    }
 
 
	return 0;
}
*/
 
// LCA  보다 느림
class LCA2
{
	int_vector P;
	int_vector R;
	int_vector V;
	int_vector_2d adjList;
public:
	LCA2(int nrNode) : P(nrNode+1), R(nrNode +1), V(nrNode +1), adjList(nrNode +1) {}
	int getLCA(int n1, int n2)
	{
		if (R[n1] < R[n2])
			swap(n1, n2);
 
		int dff = R[n1] - R[n2];
 
		for (int i = 0; i < dff; i++)
			n1 = P[n1];
 
		while (n1 != n2)
		{
			n1 = P[n1];
			n2 = P[n2];
		}
		return n1;
	}
	void addNode(int n1, int n2)
	{
		adjList[n1].push_back(n2);
		adjList[n2].push_back(n1);
	}
 
	void BFS(int root)
	{
		queue<int> q;
		q.push(root);
		P[root] = root;
 
		while (!q.empty())
		{
			auto top = q.front();
			q.pop();
 
			V[top] = true;
			for (auto &c : adjList[top])
			{
				if (V[c])
					continue;
 
				P[c] = top;
				R[c] = R[top] + 1;
				q.push(c);
			}
		}
	}
};
 
// LCA 에서 Weight
class LcaWeight
{
	int_vector_2d p;
	int_pair_vector_2d edge;
	int_vector tin, tout;
	int timer;
	int log;
    int_vector lengthFromRoot;
    int nrNode_ = 0;
public:
	LcaWeight(int nrNode) : edge(nrNode + 1), tin(nrNode +1), tout(nrNode+1), timer(0), lengthFromRoot(nrNode+1)
	{
		for (log = 1; (1 << log) <= nrNode; log++);
		log -= 1;
 
		p.resize(nrNode + 1, vector<int>(log+1, 0));
 
        nrNode_ = nrNode;
	}
	void addEdge(int& n1, int& n2, int &w)
	{
		edge[n1].push_back(make_pair(n2, w));
		edge[n2].push_back(make_pair(n1, w));
	}
	void dfs(int v, int parent) {
		tin[v] = ++timer;
		p[v][0] = parent;
		for (int i = 1; i <= log; i++)
		{
			p[v][i] = p[p[v][i - 1]][i - 1];
		}
		for (auto& to : edge[v]) {
			if (to.first != parent) {
				dfs(to.first, v);
			}
		}
		tout[v] = ++timer;
	}
 
    void updateLength(int root)
    {
        vector<bool> v(nrNode_+1, false);
		queue<int> q;
		q.push(root);
 
		while (!q.empty())
		{
			auto top = q.front();
			q.pop();
 
			v[top] = true;
			for (auto &c : edge[top])
			{
				if (v[c.first])
					continue;
                lengthFromRoot[c.first] = lengthFromRoot[top] + c.second;
				q.push(c.first);
			}
		}
    }
    int getDistance(int u, int v)
    {
        int cp = getLca(u,v);
        int ans = lengthFromRoot[u] + lengthFromRoot[v] - lengthFromRoot[cp] * 2;
        return ans;
    }
 
	int getLca(int u, int v)
	{
		if (upper(u, v)) return u;
		if (upper(v, u)) return v;
 
		for (int i = log; i >= 0; i--)
		{
			if (!upper(p[u][i], v))
			{
				u = p[u][i];
 
			}
		}
		return p[u][0];
	}
 
private:
	bool upper(int u, int v)
	{
		return (tin[u] <= tin[v] && tout[u] >= tout[v]);
	}
};
 
 
// LCA Weight 예제
/*
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
 
    int nrNode;
    cin >> nrNode;
 
    LcaWeight lcaw(nrNode);
 
    FOR(i, nrNode-1)
    {
        int n1, n2, w;
        cin >> n1 >> n2 >> w;
        lcaw.addEdge(n1, n2, w);
    }
    lcaw.dfs(1,1);
    lcaw.updateLength(1);
 
    int nrQ;
    cin >> nrQ;
 
    FOR(i, nrQ)
    {
        int n1, n2;
        cin >> n1 >> n2;
 
        int ans = lcaw.getDistance(n1,n2);
        cout << ans << "\n";
    }
 
 
	return 0;
}
 
*/
 
 
#define CHECK_BIT_LL(X, I) ((X) & (1LL<<(I)))
#define BIT_INV_LL(X, I) (X) ^= (1LL<<(I))
 
#define BIT_SET_LL(X, I) (X) |= (1LL<<I)
#define BIT_CLEAR_LL(X, I) (X) &= ~(1LL<<I)
 
 
#define BOOL_INV(X) (x) ^= true
#define CHECK_BIT(X, I) ((X) & (1<<(I)))
#define BIT_INV(X, I) (X) ^= (1<<(I))
 
#define BIT_SET(X, I) (X) |= (1<<(I))
#define BIT_CLEAR(X, I) (X) &= ~(1<<(I))
 
 
#define MOD_DEFAULT 1000000007LL
 
 
ll getLCM_WithLimit(ll a, ll b, ll ANS_LIMIT)
{
	if(a >= ANS_LIMIT || b >= ANS_LIMIT)
		return ANS_LIMIT;
	ll tmp = (a / gcd(a,b)) * b;
	if(tmp >= ANS_LIMIT)
		return ANS_LIMIT;
	return tmp;
}
 
/*
    lambda(람다식) expression 을 이용한 정렬
 
    sort(myPair.begin(), myPair.end(), [](int_pair &a, int_pair &b){
        if(a.first == b.first)
            return a.second < b.second; // 오름 차순 정렬
 
        return a.first > b.first; // 내림 차순 정렬
    });
 
*/
 
 
// 그래프의 정점과 가중치를 나타내는 구조체
struct Edge {
    int to, weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};
 
// 다익스트라 알고리즘 함수
void dijkstra(vector<vector<Edge>>& graph, int start, vector<int>& dist) {
    int numNodes = graph.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
 
    dist.assign(numNodes, INT_MAX);
    dist[start] = 0;
    pq.push({0, start});
 
    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();
 
        if (dist_u != dist[u]) {
            continue; // 더 짧은 경로가 이미 계산되었을 경우, 무시
        }
 
        for (const Edge& edge : graph[u]) {
            if (dist[u] != INT_MAX && dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                pq.push({dist[edge.to], edge.to});
            }
        }
    }
}
 
 
 
 
ll getLCM(ll a, ll b)
{
	ll tmp = (a / gcd(a,b)) * b;
	return tmp;
}
 
ll getLCMForList(ll_vector &list)
{
	ll ans = 1;
	for(auto &l : list)
		ans = getLCM(ans, l);
	return ans;
}
 
 
 
/*
    lambda(람다식) expression 을 이용한 정렬
 
    sort(myPair.begin(), myPair.end(), [](int_pair &a, int_pair &b){
        if(a.first == b.first)
            return a.second < b.second; // 오름 차순 정렬
 
        return a.first > b.first; // 내림 차순 정렬
    });
 
*/
 
 
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
 
/*
struct S {
    ll a;
    ll size;
};
 
struct F {
    ll a, b;
};
 
S op(S l, S r) { return S{l.a + r.a, l.size + r.size}; }
 
S e() { return S{0, 0}; }
 
S mapping(F l, S r) { return S{r.a * l.a + r.size * l.b, r.size}; }
 
F composition(F l, F r) { return F{r.a * l.a, r.b * l.a + l.b}; }
 
F id() { return F{1, 0}; }
*/
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
 
//using namespace at_segtree;
 
//ll op(ll a, ll b) { return min(a, b); }
 
//ll e() { return LONG_LONG_MAX; }
 
//ll_vector a { 55, 20, 5 , 6, 17, 2};
//segtree<ll, op, e> seg(a);
 
 
 
 
// lower_bound는 찾고자 하는 값보다 크거나 같은 값 중 가장 처음 나오는 값의 반복자를 반환합니다.
// lower bound 의 원소의 개수 :  int count = std::distance(vec.begin(), it);
// upper_bound는 찾고자 하는 값보다 큰 값 중 처음 나오는 값을 반환합니다.
// lower_bound는 upper_bound에서 찾고자 하는 값과 같은 경우가 더해진 것 입니다.
 
void testLowerBound()
{
	int_vector v { 1,2,5,7, 10 , 15, 19, 22};
	auto it = lower_bound(v.begin(), v.end(), 12);
 
	cout << *it << "," << distance(v.begin(), it) << endl;
	//출력 : 15,5
}
 
// 좌표 압축
 
/*
	// 원 데이터 정렬
	sort(rawData.begin(), rawData.end());
 
	// 중복 제거
	rawData.erase(unique(rawData.begin(),rawData.end()), rawData.end());
 
    // 각 원본 데이터별 2진 탐색으로 압축 좌표 획득. +1 을 하는 이유는 1 base 로 설정하기 위함.
	FOR(i, nrStation)
	{
		auto it = lower_bound(rawData.begin(), rawData.end(), stations[i]);
		int newCoord = distance(rawData.begin(), it) +1;
 
		stations[i] = newCoord;
	}
*/
 
//인접 좌표 이동
/*
    int_vector_2d moving {
        {0, -1}, {0, 1}, {-1, 0}, {1,0}
    };
*/
 
// 벨만 포드 알고리즘 예시
/*
#include <iostream>
#include <vector>
#include <climits>
 
using namespace std;
 
struct Edge {
    int source, destination, weight;
};
 
class Graph {
public:
    int V, E;
    vector<Edge> edges;
 
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }
 
    void addEdge(int source, int destination, int weight) {
        edges.push_back({source, destination, weight});
    }
 
    void bellmanFord(int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;
 
        for (int i = 1; i <= V - 1; i++) {
            for (int j = 0; j < E; j++) {
                int u = edges[j].source;
                int v = edges[j].destination;
                int weight = edges[j].weight;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
 
        bool hasNegativeCycle = false;
        for (int j = 0; j < E; j++) {
            int u = edges[j].source;
            int v = edges[j].destination;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                hasNegativeCycle = true;
                break;
            }
        }
 
        if (hasNegativeCycle) {
            cout << "Graph contains negative weight cycle" << endl;
        } else {
            printArr(dist);
        }
    }
 
    void printArr(vector<int>& dist) {
        cout << "Vertex   Distance from Source" << endl;
        for (int i = 0; i < V; ++i)
            cout << i << "\t\t" << dist[i] << endl;
    }
};
 
int main() {
    int V = 5; // Number of vertices in graph
    int E = 8; // Number of edges in graph
    Graph graph(V, E);
 
    // adding edges to the graph
    graph.addEdge(0, 1, -1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(3, 2, 5);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 3, -3);
 
    int src = 0; // Source vertex
    graph.bellmanFord(src);
 
    return 0;
}
 
*/
// 최장 공통 부분 수열 문제. 두 문자열의 LCS 계산
/*
void LCS(string &s1, string &s2)
{
    int_vector_2d LCS(s1.size()+1, int_vector(s2.size()+1, 0));
 
    for(int i = 1; i <= (int)s1.size() ; i++)
    {
        for(int j = 1 ; j <= (int)s2.size() ; j++)
        {
            if(s1[i-1] == s2[j-1])
            {
                LCS[i][j] = LCS[i-1][j-1] + 1;
            }
            else
            {
                LCS[i][j] = max(LCS[i][j-1], LCS[i-1][j]);
            }
        }
    }
    cout << LCS[s1.size()][s2.size()] << endl;
 
    int i = s1.size();
    int j = s2.size();
 
    string ans;
 
    while(i > 0 && j > 0)
    {
        if(s1[i-1] == s2[j-1]) {
            ans.push_back(s1[i-1]);
            --i;
            --j;
        }
        else
        {
            if(LCS[i-1][j] > LCS[i][j-1])
            {
                --i;
            }
            else
            {
                --j;
            }
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
}
*/
 
// 플로이드 워셀 알고리즘. 그래프르의 모든 노드간 최단거리 구하기
/*
void Floyd_Warshall(int len, int_vector_2d &adj, int_vector_2d &dist)
{
    for(int i = 1; i <= len; i++){
        for(int j =1; j <= len; j++){
            if (i == j) dist[i][j] = 0;
            else if (adj[i][j]) dist[i][j] = adj[i][j];
            else dist[i][j] = inf;
        }
    }
    for(int k = 1; k<= len ; k++){
        for(int i = 1; i <= len ; i++){
            for(int j = 1; j <= len ; j++){
                dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
            }
        }
    }
}
*/
 
// 피보나치 수의 빠른 계산
// 행렬의 빠른 거듭 제곱으로 계산 할 수 있다 (단 n-1 번 곱해야 함.)
/*
    ll_vector_2d mat{
        {1,1},
        {1,0}
    };
    auto ans = matrixPow(mat, n-1);
 
*/
 
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
 
 
#define INF_1E97 ((int)1e9+7)
#define INF_1E187 ((ll)1e18+7)
#define INF_1E127 ((ll)1e12+7)
 
template <typename T>
void printPair(string prefix, pair<T, T> &p)
{
    cout << prefix << " : " << p.first << "," << p.second << endl;
}
 
int moving[4][2] = {
    {0, -1}, {0, 1}, {-1, 0}, {1,0}
};
 
/*
int_vector_2d moving {
    {0, -1}, {0, 1}, {-1, 0}, {1,0}
};
*/
 
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
 
 
 
// X 보다 비트 count 가 1개 적은 sub mask 구하기
std::vector<int> getSubmasksWithOneLessBit(int x) {
    std::vector<int> submasks;
    int bit = 1;
    while (bit <= x) {
        if (x & bit) {
            submasks.push_back(x & ~bit);
        }
        bit <<= 1;
    }
    return submasks;
}
 
template <typename T>
int getBitCnt(T m , int cnt)
{
    int ans = 0;
    for(int i = 0 ; i < cnt ; i++)
    {
        if(CHECK_BIT(m, i))
            ans++;
    }
    return ans;
 
}
 
string num_to_bstring(int n, int sz= 32)
{
    string ans = "b";
    for(int i = sz-1 ; i >= 0 ; i--)
    {
        if(CHECK_BIT(n, i))
        {
            ans.push_back('1');
        }
        else
        {
            ans.push_back('0');
        }
 
    }
    return ans;
}
 

 
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
 
// 단순한 이항계수 풀이
template <typename T>
void binomialCoefficient(int n, int k, vector<vector<T>> &C) {
    // 결과를 저장할 2차원 벡터 초기화
    C = vector<vector<T>>(n+1, vector<T>(k+1, 0));
 
    // 동적 프로그래밍을 사용하여 이항계수를 계산
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= std::min(i, k); ++j) {
            // k가 0이거나 n과 같으면 1
            if (j == 0 || j == i)
                C[i][j] = 1;
            else
                C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
}
 
 
#define MOD_FOR_COEFF INF_1E97
// 이항 계수 계산 함수
 
ll getPowMod(ll base, ll po)
{
	if (po == 0) return 1;
	if (po % 2 > 0)
        return (getPowMod(base, po - 1) * base) % MOD_FOR_COEFF;
	ll half = getPowMod(base, po / 2) % MOD_FOR_COEFF;
	return (half * half) % MOD_FOR_COEFF;
}
 
 
ll getBinaryCoeff(int n , int r)
{
    ll a = 1;
 
    for(int i = 1 ; i <= n ; i++)
    {
        a *= i;
        a %= MOD_FOR_COEFF;
    }
 
    ll b = 1;
 
    for(int i = 1 ; i <= n-r ; i++)
    {
        b *= i;
        b %= MOD_FOR_COEFF;
    }
 
    for(int i = 1 ; i <= r ; i++)
    {
        b *= i;
        b %= MOD_FOR_COEFF;
    }
    b = getPowMod(b , MOD_FOR_COEFF -2);
 
    ll result = (a * b) % MOD_FOR_COEFF;
 
	return result;
}
 
 
// 이항 계수 계산 함수
template <typename T>
T getPowMod2(T base, T po, T modval)
{
	if (po == 0) return 1;
	if (po % 2 > 0)
        return (getPowMod2(base, po - 1, modval) * base) % modval;
	T half = getPowMod2(base, po / 2, modval) % modval;
	return (half * half) % modval;
}
 
 
// 이항계수 계산 : n! / (r! *(n-r)!)
template <typename T>
T getBinaryCoeff2(T n , T r, T modval)
{
    T a = 1;
 
    for(T i = 1 ; i <= n ; i++)
    {
        a *= i;
        a %= modval;
    }
 
    T b = 1;
 
    for(T i = 1 ; i <= n-r ; i++)
    {
        b *= i;
        b %= modval;
    }
 
    for(T i = 1 ; i <= r ; i++)
    {
        b *= i;
        b %= modval;
    }
    b = getPowMod2(b , modval -2, modval);
 
    T result = (a * b) % modval;
 
	return result;
}
// Mod 가 좀 작은 소수일 경우 유용함.
ll getFastBinaryCoeff(ll N, ll R, ll Mod)
{
    ll ans = 1;
 
    while(N > 0 || R > 0)
    {
        ll tN = N % Mod;
        ll tR = R % Mod;
 
        N /= Mod;
        R /= Mod;
 
        //cout << "tN =" << tN << ", tR =" << tR << endl;
 
        if(tN == tR)
            continue;
        if(tN < tR)
        {
            ans = 0;
            break;
        }
        ans *= getBinaryCoeff2(tN, tR, Mod);
        ans %= Mod;
    }
    return ans;
}
 
// prefix 테이블을 만들고 구간쿼리 해 주는 함수
template <typename T>
class PrefixSum {
private:
    vector<T> prefix;

public:
    PrefixSum(vector<T>& arr) {
        prefix.resize(arr.size() + 1, T());
        for (size_t i = 0; i < arr.size(); ++i) {
            prefix[i + 1] = prefix[i] + arr[i];
        }
    }

    T query(int start, int end) {
        if (start < 0 || end >= static_cast<int>(prefix.size()) - 1 || start > end) {
            return 0;
        }
        return prefix[end + 1] - prefix[start];
    }
};

// 배열 내에서 start ~ end 를 포함하는 구간의 index 를 반환
template <typename T>
ip findRangeIndices(const std::vector<T>& arr, const T& start, const T& end) {
    auto lower = lower_bound(arr.begin(), arr.end(), start);
    auto upper = upper_bound(arr.begin(), arr.end(), end);

    int startIndex = lower - arr.begin();
    int endIndex = upper - arr.begin() - 1;

    if (lower == arr.end() || *lower < start || *lower > end || startIndex > endIndex) {
        return {-1, -1};
    }
    return {startIndex, endIndex};
}


// Strongly Connected Component 찾기 - 강한 연결 요소
class SCC {
    vector<set<int>> graph_;
    int index_{1};
    iv low_;
    iv discover_;
    stack<int> stk_;
    bv inStack_;
    iv2 sccs_;
    int sz_{0};
public:
    SCC(int sz) : graph_(sz+1), low_(sz+1), discover_(sz+1), inStack_(sz+1), sz_(sz) {}

    void addEdge(int src, int dest)
    {
        graph_[src].emplace(dest);
    }
    void DFS(int cur)
    {
        low_[cur] = discover_[cur] = index_++;
        stk_.push(cur);
        inStack_[cur] = true;

        for(auto &n : graph_[cur])
        {
            if(discover_[n] == 0)
            {
                DFS(n);
                low_[cur] = min(low_[cur], low_[n]);
            }
            else if (inStack_[n]) 
            {
                low_[cur] = min(low_[cur], discover_[n]);
            }
        }
        //cout << "low/disc =" << low_[cur] << "," << discover_[cur] << endl;
        if(low_[cur] == discover_[cur])
        {
            iv scc;
            while(true)
            {
                int w = stk_.top();
                stk_.pop();
                inStack_[w] = false;
                scc.push_back(w);
                if(cur == w)
                    break;
            }
            sccs_.push_back(scc);
        }

    }

    iv2 getSCC()
    {
        for(int i = 1 ; i <= sz_ ; i++)
        {
            if(discover_[i] == 0)
            {    
                DFS(i);
            }
        }
        return sccs_;
    }
};

/*

// 그래프에서 단절점 찾기
class GetCuttingPoint
{
    iv2 graph_;
    int N_;
    int timer_{0};
    iv order_;
    iv cutting_;
public:
    GetCuttingPoint(int n) : N_(n) {
        graph_.resize(N_ +1);

        order_.resize(N_ +1);
        cutting_.resize(N_ +1);
    }
    void addEdge(int a, int b)
    {
        graph_[a].push_back(b);
        graph_[b].push_back(a);
    }

    int DFS(int cur, bool isRoot){
        // order[i] : DFS 중 i 번째 노드를 방분한 시점
        // low : i 번째 노드 및 하위 노드들의 low 중 최소값.
        // degree : 방문하지 않은 자식노드들에 대한 순회

        order_[cur] = ++timer_;

        int low = order_[cur];

        int degree = 0;

        for(auto &n : graph_[cur])
        {
            if(order_[n] > 0)
            {
                low = min(low, order_[n]);
                continue;
            }
            int tmp = DFS(n , false);
            if(!isRoot && order_[cur] <= tmp)
            {
                // 현재 노드의 방문 순서 보다 자식노드들의 low 값이 더 크다면 현재노드는 단절점
                // 이 말은 현재노드를 방문하지 않고서 해당 자식노드를 방문할 수 없다는 뜻.
                cutting_[cur] = 1;
            }
            low = min(low, tmp);
            degree++;
        }

        if(isRoot && degree > 1)
        {
            // 현재노드가 Root 인 경우 degree 가 2 이상이면 단절점이다.
            cutting_[cur] = 1;
        }
        return low;
    }

    iv getAns()
    {
        for(int i = 1; i <= N_ ; i++)
        {
            if(order_[i] == 0)
            {
                DFS(i, true);
            }
        }
        return cutting_;
    }
};


// 그래프에서 단절선 찾기기
class GetCuttingEdges
{
    iv2 graph_;
    int N_;
    int timer_{0};
    iv discovery_;
    iv low_;
    ipv cuttings_;
public:
    GetCuttingEdges(int n) : N_(n) {
        graph_.resize(N_ +1);
        discovery_.resize(N_ +1);
        low_.resize(N_ +1);
    }
    void addEdge(int a, int b)
    {
        graph_[a].push_back(b);
        graph_[b].push_back(a);
    }

    void DFS(int cur, int parent){
        // discovery[i] : DFS 중 i 번째 노드를 방분한 시점
        // low : i 번째 노드 및 하위 노드들의 low 중 최소값.
        discovery_[cur] = low_[cur] = ++timer_;

        for(auto &n : graph_[cur])
        {
            if(n == parent)
                continue;
            
            if(discovery_[n] > 0)
            {
                low_[cur] = min(low_[cur], discovery_[n]);
                continue;
            }
            DFS(n , cur);
            low_[cur] = min(low_[cur], low_[n]);

            if(low_[n] > discovery_[cur])
            {
                cuttings_.push_back(make_pair(cur, n));
            }

        }
    }

    ipv getAns()
    {
        for(int i = 1; i <= N_ ; i++)
        {
            if(discovery_[i] == 0)
            {
                DFS(i, -1);
            }
        }
        return cuttings_;
    }
};

template <typename T>
struct NetworkFlow
{
	T INF{0};
	int nrNode{0};
	vector<vector<T>> c;
	vector<vector<T>> f;
	iv2 v;
	iv parent;

	NetworkFlow(int n, T inf)
	{
        nrNode = n;
        INF = inf;
		parent.resize(nrNode);
		c.resize(nrNode);

		for (int i = 0; i < nrNode; i++)
		{
			c[i].resize(nrNode);
			fill(c[i].begin(), c[i].end(), 0);
		}
		f = c;

		v.resize(nrNode);
	}
	T residual(int here, int there)
	{
		return c[here][there] - f[here][there];
	}

	T min2(T a, T b) {
		return (a > b) ? b : a;
	}

	T edmonds_karp(int source, int sink) {
		T total = 0;
		while (true) {
			fill(parent.begin(), parent.end(), -1);
			queue<int> Q;
			Q.push(source);
			parent[source] = source;
			while (!Q.empty() && parent[sink] == -1) {
				int here = Q.front();
				Q.pop();
				for (int there : v[here]) {
					if (residual(here, there) > 0 && parent[there] == -1) {
						parent[there] = here;
						Q.push(there);
					}
				}
			}

			if (parent[sink] == -1) break;

			T mn = INF;
			for (int p = sink; p != source; p = parent[p]) {
				mn = min2(c[parent[p]][p] - f[parent[p]][p], mn);
			}

			for (int p = sink; p != source; p = parent[p]) {
				f[parent[p]][p] += mn;
				f[p][parent[p]] -= mn;
			}
			total += mn;
		}
		return total;
	}
	void SetFlow(int src, int sink, T weight)
	{
		v[src].push_back(sink);
		v[sink].push_back(src);
		c[src][sink] = weight;
	}

};

int doubleCmp(double x, double y, double absTolerance = (1.0e-8))
{
    double diff = x - y;
    if (fabs(diff) <= absTolerance)
        return 0;

    return (diff > 0) ? 1 : -1;
}

*/

// 기울기 단조 감소 할때 최소값, 단조 증가할때 최대값을 구할 수 있다.
class CHT {
    struct Line {
        ll m; // 기울기
        ll c; // y 절편
    };

    double intersec(Line &A, Line B)
    {
        return (double)(B.c - A.c) / (A.m - B.m);
    }

    vector<Line> Hull;
public:
    void addLine(ll m, ll c) {
        Line newLine{m,c};
        while(Hull.size() >= 2)
        {
            int sz = Hull.size();
            if( intersec(Hull[sz-2], Hull[sz-1]) >= 
                        intersec(Hull[sz-1], newLine) )
            {
                Hull.pop_back();
            }
            else
            {
                break;
            }
        }
        Hull.push_back(newLine);
    }


    ll query(ll x) {
        int ans = 0;
        
        int low = 0;
        int high = Hull.size() - 2;
 
        while (low <= high) {
            int mid = low + (high - low) / 2;

            double m = intersec(Hull[mid], Hull[mid+1]);

    
            if (m < x)
            {
                low = mid + 1;
                ans = mid+1;
            }
            else
            {
                high = mid - 1;
                ans = mid;
            }
        }
        return Hull[ans].m * x + Hull[ans].c;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    int T;
    cin >> T;

    int maxLen = 0;

    iv arr(T);
    FOR(i, T)
    {
        cin >> arr[i];
        maxLen = max(maxLen, arr[i]);
    }

    // 0 : 완전 공백 - 공백,흑,백
    // 1 : 백 + 공백 - 공백, 흑, 백
    // 2 : 흑 + 공백 - 공백, 백, 흑
    // 3 : 공백 + 흑 - 공백, 흑, 백
    // 4 : 공백 + 백 - 공백, 흑, 백
    // 5 : 막힌 흑 - 공백, 흑
    // 6 : 막힌 백 - 공백, 백

    llv2 DP(maxLen+1, llv(7));

    DP[1][0] = 1;
    DP[1][5] = 1;
    DP[1][6] = 1;

    for(int i = 1 ; i < maxLen ; i++)
    {
        DP[i+1][0] = DP[i][0];
        DP[i+1][1] = DP[i][1] + DP[i][4] + DP[i][6];
        DP[i+1][2] = DP[i][2] + DP[i][3] + DP[i][5];
        DP[i+1][3] = DP[i][0] + DP[i][1] + DP[i][2] + DP[i][3];
        DP[i+1][4] = DP[i][0] + DP[i][1] + DP[i][2] + DP[i][4];
        DP[i+1][5] = DP[i][5] + DP[i][4];
        DP[i+1][6] = DP[i][6] + DP[i][3];

        for(int j = 0 ; j < 7 ; j++)
        {
            DP[i+1][j] %= INF_1E97;
        }
    }

    for(auto a : arr)
    {
        ll ans = 0;
        FOR(j , 5)
        {
            ans += DP[a][j];
            ans %= INF_1E97;
        }
        cout << ans << endl;
    }


    return 0;
}