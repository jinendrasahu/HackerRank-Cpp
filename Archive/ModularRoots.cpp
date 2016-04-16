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

const int dd[] = {1, 0, -1, 0};

tuple<ll, ll, ll> gcd(ll a, ll b)
{
    if (a == 0) return make_tuple(b, 0, 1);
    ll g, x, y;
    tie(g, x, y) = gcd(b % a, a);
    auto tmp = x;
    x = y - (b / a) * x;
    y = tmp;
    return make_tuple(g, x, y);
}

ll modInv(ll x, ll m)
{
    ll g, a, b;
    tie(g, a, b) = gcd(x, m);
    assert(1 == g);
    if (a < 0) a += m;
    assert(0 < a);
    assert(a < m);
    return a;
}

// ax = b (mod m)
vector<ll> solve(ll a, ll b, ll m)
{
    ll g, ga, gb;
    a %= m;
    b %= m;
    tie(g, ga, gb) = gcd(a, m);
    if (1 == g) return {(modInv(a, m) * b) % m};
    if (m == g) {
        if (b % g != 0) return {};
        vector<ll> v;
        REP(i, m) v.push_back(i);
        return v;
    };
    if (0 != b % g) return {};
    auto v = solve(a / g, b / g, m / g);
    assert(1 == v.size());
    FOR(i, 1, g - 1) v.push_back((v[0] + (m / g) * i) % m);
    return v;
}

vector<ll> primes(ll pMax)
{
    vector<ll> p;
    p.reserve(sqrt(pMax));
    p.push_back(2);
    int x = 3;
    bool ok;
    for (;;) {
        int last = p.size() - 1;
        if (pMax <= p[last]) break;
        ok = true;
        for (int i = 0; i < last and p[i] * p[i] <= x; ++i) {
            if (x % p[i] == 0) {
                ok = false;
                break;
            }
        }
        if (ok) p.push_back(x);
        x += 2;
    }
    return p;
}

// x^n % m
ll powMod(ll x, ll n, ll m)
{
    ll res = 1;
    vector<bool> bm;
    while (0 < n) {
        bm.push_back((n & 1) != 0);
        n /= 2;
    }
    reverse(ALL(bm));
    for (bool b : bm) {
        res = SQR(res) % m;
        if (b) res *= x;
        res %= m;
    }
    return res;
}

// find primitive root of a prime p
ll proot(ll p)
{
    if (p == 2) return 1;
    if (p == 3) return 2;
    auto s = p - 1;
    auto pv = primes(sqrt(s) + 1);
    vector<ll> pdiv;
    for (auto p : pv) if (0 == s % p) pdiv.push_back(p);
    FOR(x, 2, s) {
        bool ok = true;
        for (auto pd : pdiv) if (1 == powMod(x, s / pd, p)) {
            ok = false;
            break;
        }
        if (ok) return x;
    }
    assert(false);
    return -1;
}

constexpr int N = 5 * 1e6;
ll dlog[N + 1] = {};

//sstrm testData(R"(29 3
//4 -4
//7 10
//111 32)");

sstrm testData(R"(3 9
2 -3
2 -2
2 -1
2 0
2 1
2 2
2 3
2 4
2 5)");

int main( int argc, char* argv[] )
{
    auto& input = testData;
    ll p, Q;
    input >> p >> Q;
    const auto root = proot(p);
    auto x = root;
    FOR(i, 1, p - 1) {
        dlog[x] = i;
        x *= root;
        x %= p;
    }
    REP(i, Q) {
        ll k, n;
        input >> k >> n;
        if (n < 0) n = p + n % p;
        n %= p;
        if (0 == n) {
            cout << 0 << '\n';
            continue;
        }
        if (2 == p) {
            cout << n << '\n';
            continue;
        }
        auto l = dlog[n];
        assert(0 != l);
        auto v = solve(k, l, p - 1);
        if (v.empty()) {
            cout << "NONE" << '\n';
            continue;
        }
        for (auto& x : v) {
            x = powMod(root, x, p);
        }
        sort(ALL(v));
        for (auto x : v) {
            cout << x << " ";
        }
        cout << '\n';
    }
    return 0;
}

