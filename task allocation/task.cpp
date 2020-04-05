/*input
5 10
1 2 
2 5
5 1
2 4
2 3
3 4
4 3
3 1
4 5	
4 1
*/


//assic value of ('0'-'9') is(48 - 57) and (a-z) is (97-122) and (A-Z) is(65-90) and 32 for space
#include<bits/stdc++.h>
using namespace std;
#define ll          long long
#define pb          push_back
#define pii         pair<ll int,ll int>
#define vpii        vector< pii >
#define vi          vector<ll int>
#define vs			vector< string >
#define vvi         vector< vector< ll > >
#define inf			(ll)1e18
#define all(it,a)   for(auto it=(a).begin();it!=(a).end();it++) 
#define F           first
#define S           second
#define sz(x)       (ll int)x.size()
#define rep(i,a,b)	for(ll int i=a;i<b;i++)
#define repr(i,a,b) for(ll int i=a;i>b;i--)
#define lbnd        lower_bound
#define ubnd        upper_bound
#define mp          make_pair
#define whatis(x)   cout << #x << " is " << x << "\n";
#define graph(n)    adj(n,vector< ll > () )
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll N = 1e5+5;
vector<vpii> adj(N, vpii());
vi vis(N,0),parent(N,0);
map< pii,ll > edge;
vi path_w;
vvi costMatrix;
ll n,m;

void init()
{
	cin>>n>>m;
	rep(i,0,m)
	{
		ll x,y,w;cin>>x>>y;
		w=rng()%100;
		x--,y--;
		adj[x].pb(mp(y,w));
		edge[mp(x,y)]=w;
	}
	// whatis(sz(adj[0]));
	return ;
}

void dfs(ll u,ll p)
{
	vis[u]=1;
	parent[u]=p;
	rep(i,0,sz(adj[u]))
	{
		ll ch = adj[u][i].F;
		if(ch==0)
		{
			ll tot = edge[mp(u,0)];
			ll cur = u;
			while(parent[cur]!=-1)
			{
				tot+=edge[mp(parent[cur],cur)];
				cur=parent[cur];
			}
			path_w.pb(tot);
		} 
		else if(vis[ch]==0)	dfs(ch,u);
	}

	return ;

}

void findCostMatrix()
{
	ll t = sz(path_w);
	// whatis(t);
	vvi ans(t,vi (t));
	rep(i,0,t) rep(j,0,t) ans[i][j] = path_w[i]+path_w[j];
	costMatrix = ans;
	cout<<"CostMatrix is : \n";
	rep(i,0,t) { rep(j,0,t) cout<<costMatrix[i][j]<<" "; cout<<"\n"; }
	cout<<"\n";
	return ;
}

ll findBestPath(ll st)
{
	ll last = st;
	ll t = sz(path_w);
	rep(i,0,10)
	{
		ll ans = inf;
		ll cur = -1;
		rep(j,0,t)
		{
			ll temp_ans;
			if(j==last) temp_ans = costMatrix[last][j];
			else temp_ans = costMatrix[last][j] + costMatrix[j][j];
			
			if(temp_ans<ans) ans=temp_ans,cur=j;
		}

		last=cur;
		cout<<"Time: "<<i+1<<" "<<last<<"\n";
	}
	return 0;
}


ll findBestPath2(ll st)
{
	ll last = st;
	ll t = sz(path_w);
	rep(i,0,10)
	{

		rep(j,0,t) rep(k,0,t) costMatrix[j][k] = rng()%100;

		ll ans = inf;
		ll cur = -1;
		rep(j,0,t)
		{
			ll temp_ans;
			if(j==last) temp_ans = costMatrix[last][j];
			else temp_ans = costMatrix[last][j] + costMatrix[j][j];
			
			if(temp_ans<ans) ans=temp_ans,cur=j;
			// cout<<temp_ans<<"\n";
		}

		last=cur;
		cout<<"Time: "<<i+1<<" "<<last<<"\n";
	}
	return 0;
}






int solve()
{
	init();
	dfs(0,-1);
	findCostMatrix();
	ll st = 2;
	cout<<"Starting state is : "<<st<<"\n";
	findBestPath(st);

	cout<<"\nStarting state is : "<<st<<"\n";
	findBestPath2(st);
	return 0;
}

int main()
{
	auto start = chrono::high_resolution_clock::now();

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll test_cases=1;
	//cin>>test_cases;
	while(test_cases--)
		solve();

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
	// cout<<"\nduration: "<<(double)duration.count()<<" milliseconds";
}