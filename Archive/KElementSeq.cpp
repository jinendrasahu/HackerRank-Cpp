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

const int dd[] = {1, 0, -1, 0};

sstrm testData(R"(3
4 3
5 2
7 7)");

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

const int M = 2e6 + 1;
ll fac[M];
ll finv[M];

ll bn(ll n, ll k)
{
    return mul(mul(fac[n], finv[k]), finv[n - k]);
}

int main( int argc, char* argv[] )
{
    fac[0] = 1;
    fac[1] = 1;
    FOR(i, 2, M - 1) fac[i] = mul(fac[i - 1], i);
    REP(i, M) finv[i] = dg(fac[i], mod - 2);
    auto& input = testData;
    ll T, K, N;
    input >> T;
    REP(i, T) {
        input >> N >> K;
        ll n = N - K;
        ll k = K;
        cout << bn(n + k - 1, n) << endl;
    }
    return 0;
}

