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
#include <unordered_map>

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
#define RFOR(k, a, b) for (decltype(a) k = (a); (b) <= k; --k)
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

sstrm testData(R"(3
3 2 1)");

//sstrm testData(R"(10
//5 4 3 2 1 2 3 4 5 6)");

//sstrm testData(R"(10
//1 2 3 2 1 0 1 2 3 4)");

constexpr ll mod = 1e9 + 7;

int main( int argc, char* argv[] )
{
    auto& input = testData;
    ll N;
    input >> N;
    vector<ll> a(N);
    REP(i, N) {
        input >> a[i];
    }
    vector<ll> l1(N);
    l1[0] = 0;
    FOR(i, 1, N - 1) {
        int j = i;
        while (0 <= j - 1 && a[i] <= a[j - 1]) {
            // cerr << "j:" << j << " a[j - 1]:" << l1[j - 1] << endl;
            j -= l1[j - 1] + 1;
        }
        l1[i] = i - j;
    }
    vector<ll> l2(N);
    l2[N - 1] = 0;
    RFOR(i, N - 2, 0) {
        int j = i;
        while (j + 1 < N && a[i] <= a[j + 1]) {
            j += l2[j + 1] + 1;
        }
        l2[i] = j - i;
    }
    unordered_map<ll, ll> imax;
    unordered_map<ll, ll> iall;
    unordered_map<ll, ll> isum;

    for (auto& pp : imax) {
        ll ai = pp.first;


    }



    // for (ll x : l2) cerr << x << endl;
    vector<ll> lt(N);
    REP(i, N) lt[i] = ((l1[i] + 1) * (l2[i] + 1)) % mod;
    vector<ll> la(N);
    REP(i, N) {
        ll len = l1[i] + l2[i] + 1;
        la[i] = len * (len - 1) / 2;
    }
    vector<pair<ll, ll>> v(N);
    REP(i, N) v[i] = make_pair(a[i], la[i]);
    for (auto& pp : v) {
        cerr << pp.first << " " << pp.second << endl;
    }
    cerr << endl;
    sort(ALL(v));
    reverse(ALL(v));
    FOR(i, 1, N - 1) {
        v[i].second += v[i - 1].second;
        v[i].second %= mod;
    }
    for (auto& pp : v) {
        cerr << pp.first << " " << pp.second << endl;
    }
    unordered_map<ll, ll> ml;
    REP(i, N) ml[a[i]] = lt[i];
    unordered_map<ll, ll> ma;
    REP(i, N) ma[a[i]] = la[i];
    unordered_map<ll, ll> mv;
    REP(i, N) mv[v[i].first] = v[i].second;
    ll ans = 0;
    cerr << endl;
    for (auto& pp : ml) {
        ll ai = pp.first;
        ll li = pp.second;
        ll lai = ma[ai];
        ll lvi = mv[ai];
        assert (li <= lvi);
        cerr << ans << " += " << ai << " * " << li << " * " << lvi - li << endl;
        ans += (((ai * li) % mod) * ((lvi - li) % mod)) % mod;
        ans %= mod;
    }
    // cout << ans << endl;
    return 0;
}
