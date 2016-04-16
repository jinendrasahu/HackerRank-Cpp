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

sstrm testData(R"(4
0 0 0
2 0 0
2 2 1
0 2 1)");

constexpr double pi = 3.141592653589793238462643383279502884L;

int main( int argc, char* argv[] )
{
    auto& input = testData;
    cout << fixed << setprecision(12);
    cerr << fixed << setprecision(12);
    ll N;
    input >> N;
    vector<double> x(N), y(N), z(N);
    REP(i, N) input >> x[i] >> y[i] >> z[i];
    auto lensq = [&](int i, int j) {
        return SQR(x[i] - x[j]) + SQR(y[i] - y[j]) + SQR(z[i] - z[j]);
    };
    auto dot = [&](int i, int j, int k) {
        int xji = x[i] - x[j];
        int yji = y[i] - y[j];
        int zji = z[i] - z[j];
        int xjk = x[k] - x[j];
        int yjk = y[k] - y[j];
        int zjk = z[k] - z[j];
        return xji * xjk + yji * yjk + zji * zjk;
    };
    auto angle = [&](int i, int j, int k) {
        return acos(dot(i, j, k) / sqrt(lensq(i, j) * lensq(j, k)));
    };
    double asum = 0;
    int cnt = 0;
    REP(i, N) FOR(j, i + 1, N - 1) FOR(k, j + 1, N - 1) {
        auto a = angle(i, j, k);
        // cerr << "angle(i: " << i << ", j: " << j << ", k: " << k << ") = " << a << endl;
        asum += a;
        ++cnt;
    }
    cout << asum / cnt << endl;
    return 0;
}

