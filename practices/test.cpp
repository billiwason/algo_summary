#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll cost(const vector<int>& A, const vector<int>& B, int L){
    ll res = A[0]-1;                        // A 첫 R을 맨앞으로
    for(int i=0;i<(int)A.size()-1;++i)
	{
        int tmp =  max(0, A[i+1]-B[i]);         // 경계마다 필요한 이동
		if(tmp > 0)
			res++;
	}
	int tmp = L - B.back();
	if(tmp > 0)
		res++;
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; string S1,S2;
    cin>>N>>S1>>S2;

	if(S1 == S2)
	{
		cout << 2 << endl;
		return 0;
	}
    const int L = 2*N;
    vector<int> P,Q;
    for(int i=0;i<L;++i){
        if(S1[i]=='R') P.push_back(i+1);
        if(S2[i]=='R') Q.push_back(i+1);
    }
    cout<<min(cost(P,Q,L), cost(Q,P,L))<<'\n';
}