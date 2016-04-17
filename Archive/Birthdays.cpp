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
using ld = long double;

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
0.100
0.200
1.000)");

ld pf(int n)
{
    if (n < 2) return 0;
    if (100 <= n) return 1;
    int m = n / 4;
    n -= m;
    ld res = 1;
    FOR(i, 1, n) res *= ld(365 - i + 1) / 365;
    FOR(i, 1, m) res *= ld(366 - n - i + 1) / 366;
    return 1 - res;
}

int main( int argc, char* argv[] )
{
    // REP(i, 100) cerr << i << " " << pf(i) << endl;
    auto& input = testData;
    ll Q;
    input >> Q;
    REP(i, Q) {
        double p;
        input >> p;
        bool found = false;
        REP(i, 100) if (p <= pf(i)) {
            cout << i << endl;
            found = true;
            break;
        }
        if (!found) cout << 366 << endl;
    }
    return 0;
}

