#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <numeric>
#include <tuple>
#include <valarray>
#include <cassert>
#include <cstring>
#include <typeinfo>
#include <functional>
#include <memory>
#include <regex>
#include <iomanip>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using sstrm = stringstream;

#define ZERO(a) std::memset((a), 0, sizeof(a))
#define FILL1D(a, v) std::fill_n(a, sizeof(a) / sizeof(a[0]), v)
#define FILL2D(a, v) std::fill_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), v)
#define FILL3D(a, v) std::fill_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), v)
#define FILL4D(a, v) std::fill_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), v)
#define COPY1D(a, b) std::copy_n(a, sizeof(a) / sizeof(a[0]), b)
#define COPY2D(a, b) std::copy_n(&a[0][0], sizeof(a) / sizeof(a[0][0]), &b[0][0])
#define COPY3D(a, b) std::copy_n(&a[0][0][0], sizeof(a) / sizeof(a[0][0][0]), &b[0][0][0])
#define COPY4D(a, b) std::copy_n(&a[0][0][0][0], sizeof(a) / sizeof(a[0][0][0][0]), &b[0][0][0][0])
#define FOR(k, a, b) for (decltype(a) k = (a); k <= (b); ++k)
#define REP(k, a) for (int k = 0; k < (a); ++k)
#define SQR(x) ((x) * (x))
#define PW(x) (1ll << (x))
#define BCNT(x) __builtin_popcountll(x)
#define LZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_clzll(x))
#define RZC(x) ((x) == 0 ? sizeof(x) * 8 : __builtin_ctzll(x))
#define ALL(c) (c).begin(),(c).end()
#define HAS(c, x) ((c).find(x) != (c).end())
#define CHAS(c,x) (find(ALL(c), x) != (c).end())

template<typename S, typename T> inline void chmin(S& a, T b) { if (b < a) a = b; }
template<typename S, typename T> inline void chmax(S& a, T b) { if (a < b) a = b; }

constexpr int M = 100000 + 1;

constexpr ll mod = 1e9 + 7;

ll add(ll a, ll b)
{
    return (a + b) % mod;
}

ll mul(ll a, ll b)
{
    return (a * b) % mod;
}

ll dg(ll a, ll k)
{
    ll res = 1;
    while (k) {
        if (k & 1) res = mul(res, a);
        k /= 2;
        a = mul(a, a);
    }
    return res;
}

map<ll, ll> mem;

ll bn(ll n, ll k)
{
    if (n == 0 || k == 0 || n == k) return 1;
    if (n < k) return 0;
    assert (mem.find(n) != mem.end());
    assert (mem.find(k) != mem.end());
    assert (mem.find(n - k) != mem.end());
    ll num = mem[n];
    ll d1 = mem[k];
    ll d2 = mem[n - k];
    return mul(mul(num, dg(d1, mod - 2)), dg(d2, mod - 2));
}

sstrm testData(R"(1 0 2 0)");
// 5

void cache(vector<ll> v)
{
    ll c = 1;
    for (ll i = 1; i <= 200001; ++i) {
        c = mul(c, i);
        for (ll x : v) if (i == x) mem[x] = c;
    }
}

int main( int argc, char* argv[] )
{
    auto cnt = [](ll g, ll e) { return bn(g + e - 1, e); };
    auto& in = testData;
    ll A, B, C, D;
    in >> A >> B >> C >> D;
    // A = RR
    // B = RB
    // C = BB
    // D = BR
    if (1 < abs(B - D)) {
        cout << 0 << endl;
        return 0;
    }
    if (B == D) {
        cache({B + A, A, B, B + C - 1, C, B - 1, B + A - 1, B + C});
        ll r1 = mul(1, cnt(B + 1, A));
        r1 = mul(r1, cnt(B, C));
        ll r2 = mul(1, cnt(B, A));
        r2 = mul(r2, cnt(B + 1, C));
        cout << add(r1, r2) << endl;
    }
    else {
        const ll bd = max(B, D);
        cache({bd + A - 1, A, bd - 1, bd + C - 1, C});
        ll r = mul(1, cnt(bd, A));
        cout << mul(r, cnt(bd, C)) << endl;
    }
    return 0;
}

