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




/**********************Code Starts from here*****************************/

ll nxn = 1e6;
vector<ll>tree(nxn);
vector<ll>arr(nxn);
void build_tree(ll start, ll end, ll index)
{
    if(start == end)
    {
        tree[index] = arr[start];
        return;
    }

    ll mid = (start + end) / 2;
    build_tree(start, mid, 2 * index);
    build_tree(mid + 1, end, 2 * index + 1);
    tree[index] = min(tree[2 * index], tree[2 * index + 1]);
    return;
}

ll query(ll ss, ll se, ll qs, ll qe, ll index)
{
    //Complete overlap:
    //it means query completly overlaps the range covered by the current node,
    if(ss >= qs and qe >= se)
        return tree[index];

    //No overlap:
    if(qs > se or qe < ss)
        return inf;

    //Partial overlap:
    ll mid = ss + (se - ss) / 2;
    ll left = query(ss, mid, qs, qe, 2 * index);
    ll right = query(mid + 1, se, qs, qe, 2 * index + 1);
    return min(left, right);
}

//Point updates.
void update(ll idx, ll val, ll ss, ll se, ll index)
{
    //It does not lie in current range
    if(idx > se or idx < ss)
        return;

    //Reached the leaf node:
    if(ss == se)
    {
        tree[index] = val;
        return;
    }

    //Partial range coverage:
    ll mid = (ss + se) / 2;

    update(idx, val, ss, mid, 2 * index);
    update(idx, val, mid + 1, se, 2 * index + 1);
    tree[index] = min(tree[2 * index], tree[2 * index + 1]);
    return;

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

    for(int i = 1; i <= n; i++)
        cin >> arr[i];

    build_tree(1ll, n, 1ll);



    while(q--)
    {
        int type;
        ll a, b;
        cin >> type >> a >> b;

        if(type == 2)
        {
            ll ans = query(1ll, n, a, b, 1ll);
            cout << ans << "\n";
        }
        else
        {
            update(a, b, 1ll, n, 1ll);
        }


    }


    return 0;
}