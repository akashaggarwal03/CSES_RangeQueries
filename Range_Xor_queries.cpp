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

int main()
{
    FASTIO;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll n, q;
    cin >> n >> q;

    vector<ll>vect(n + 1);

    for(ll i = 1; i <= n; i++)
        cin >> vect[i];

    vector<ll>xori(n + 1);

    for(int i = 1; i <= n; i++)
    {
        xori[i] = xori[i - 1] ^ vect[i];
    }


    while(q--)
    {
        ll a, b;
        cin >> a >> b;


        ll ans = xori[b] ^ xori[a - 1];
        cout << ans << "\n";
    }


    return 0;
}