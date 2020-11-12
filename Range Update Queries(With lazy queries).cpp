#include"bits/stdc++.h"
using namespace std;

#define ll long long int
#define f(i,x,n)  for(int i=x;i<n;i++)
#define FASTIO cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
#define sz(a) int((a).size())
#define mod 1000000007
#define inf LLONG_MAX
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
template <typename T>
inline T gcd(T a, T b)
{
    while (b != 0) swap(b, a %= b);
    return a;
}

template <typename T>
inline void seethis(vector<T>vect)
{
    for(T x : vect)
        cout << x << " ";
    cout << "\n";
}

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
    cerr << *it << " = " << a << endl;
    err(++it, args...);
}
//LCM
int lcm(int a, int b)
{
    return a * (b / gcd(a, b));
}

//For sort by second
bool cmp(const pair<int, int> &a)
{
    return a.first < a.second;
}

//Tree
/* const int MAXN = 1e5 + 5;
vector<ll> adj[MAXN];*/

//ModPower
ll modpower(ll a, ll b, ll c)
{
    ll res = 1;
    while(b)
    {
        if(b & 1LL)
            res = (res * a) % c;
        a = (a * a) % c;
        b >>= 1;
    }
    return res;
}


#define nxn 1e6
vector<ll>vect(nxn);
vector<ll>tree(nxn);
vector<ll>lazy(nxn, 0);


void build_tree(ll ss, ll se, ll index)
{
    if(ss == se)
    {
        tree[index] = vect[ss];
        return;
    }

    ll mid = (ss + se) / 2;
    build_tree(ss, mid, 2 * index);
    build_tree(mid + 1, se, 2 * index + 1);
    tree[index] = tree[2 * index + 1] + tree[2 * index];
    return;

}

void lazy_update(ll ss, ll se, ll l, ll r, ll index, ll inc)
{
    //resolve current lazy value.
    if(lazy[index] != 0)
    {
        tree[index] += lazy[index];

        //non-leaf node
        if(ss != se)
        {
            lazy[2 * index] += lazy[index];
            lazy[2 * index + 1] += lazy[index];
        }

        lazy[index] = 0;
    }

    //No overlap:
    if(ss > r or se < l)
        return;

    //complete overlap:
    if(ss >= l and se <= r)
    {
        tree[index] += inc;
        if(ss != se)
        {
            lazy[2 * index] += inc;
            lazy[2 * index + 1] += inc;
        }
        return;
    }

    //partial overlap:
    ll mid = (ss + se) / 2;

    lazy_update(ss, mid, l, r, 2 * index, inc);
    lazy_update(mid + 1, se, l, r, 2 * index + 1, inc);
    tree[index] = tree[2 * index + 1] + tree[2 * index];
    return;


}

ll lazy_query(ll ss, ll se, ll qs, ll qe, ll index)
{
    if(lazy[index] != 0)
    {
        tree[index] += lazy[index];

        //non-leaf node
        if(ss != se)
        {
            lazy[2 * index] += lazy[index];
            lazy[2 * index + 1] += lazy[index];
        }

        lazy[index] = 0;
    }

    //No overlap:
    if(ss > qe or se < qs)
        return 0;

    //complete overlap:
    if(ss >= qs and se <= qe)
    {
        return tree[index];
    }

    //partial overlap:
    ll mid = (ss + se) / 2;
    ll left = lazy_query(ss, mid, qs, qe, 2 * index);
    ll right = lazy_query(mid + 1, se, qs, qe, 2 * index + 1);
    return tree[index] = left + right;


}
int main()
{
    FASTIO;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll n, q;
    cin >> n >> q;


    for(ll i = 1; i <= n; i++)
        cin >> vect[i];


    build_tree(1ll, n, 1ll);

    while(q--)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            ll l, r, inc;
            cin >> l >> r >> inc;
            // error(l, r, inc);
            lazy_update(1, n, l, r, 1, inc);
        }
        else
        {
            ll idx;
            cin >> idx;
            ll ans = lazy_query(1, n, idx, idx, 1);
            cout << ans << "\n";

        }
    }


    return 0;
}