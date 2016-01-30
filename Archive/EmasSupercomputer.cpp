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

bool G[15][15] = {false};


//sstrm testData(R"(5 6
//GGGGGG
//GBBBGB
//GGGGGG
//GGBBGB
//GGGGGG)");
// 5

sstrm testData(R"(6 6
BGBBGB
GGGGGG
BGBBGB
GGGGGG
BGBBGB
BGBBGB)");
// 25

int main( int argc, char* argv[] )
{
    auto& in = testData;
    int n, m;
    in >> n >> m;
    char c;
    REP(i, n) REP(j, m) {
        in >> c;
        if (c == 'G') G[i][j] = true;
    }
    int ret = 0;
    auto valid = [n, m](int i, int j) { return 0 <= i && i < n && 0 <= j && j < m && G[i][j]; };
    REP(xi, n) REP(xj, m) {
        if (!G[xi][xj]) continue;
        REP(xd, 15) {
            if (!valid(xi - xd, xj) || !valid(xi + xd, xj) || !valid(xi, xj - xd) || !valid(xi, xj + xd)) {
                break;
            }
            auto overlap = [n, m, xi, xj, xd](int ii, int jj) { return (ii == xi && xj - xd <= jj && jj <= xj + xd) || (xi - xd <= ii && ii <= xi + xd && jj == xj); };
            REP(yi, n) REP(yj, m) {
                int maxyd = -1;
                REP(yd, 15) {
                    if (!valid(yi - yd, yj) || !valid(yi + yd, yj) || !valid(yi, yj - yd) || !valid(yi, yj + yd) ||
                        overlap(yi - yd, yj) || overlap(yi + yd, yj) || overlap(yi, yj - yd) || overlap(yi, yj + yd)) {
                        break;
                    }
                    maxyd = yd;
                }
                if (0 <= maxyd) {
                    chmax(ret, (1 + 4 * xd) * (1 + 4 * maxyd));
                }
            }
        }
    }
    cout << ret << endl;
    return 0;
}

