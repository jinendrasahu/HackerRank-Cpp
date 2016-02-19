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


//sstrm testData(R"(3
//5 4
//1 5
//3 2
//4 1
//2 4
//4 2
//1 2
//4 3
//10 3
//2 4
//5 4
//9 8)");

sstrm testData(R"(2
5 4
1 5
3 2
4 1
2 4
4 2
1 2
4 3)");

constexpr int L = 10; // 1000
int px[2][L + 1] = {};
constexpr int MAX = L * L;

int main( int argc, char* argv[] )
{
    auto& input = testData;
    int T;
    input >> T;
    REP(i, T) {
        int M, N;
        input >> M >> N;
        FILL2D(px, MAX);
        px[0][0] = 0;
        int x, y, py = -1;
        REP(j, N) {
            int jc = j & 1;
            int jn = (j + 1) & 1;
            FILL1D(px[jn], MAX);
            input >> x >> y;
            int pyd = -1 != py ? abs(py - x) : 0;
            px[jn][0] = px[jc][0] + abs(x - y) + pyd;
            // case 1: we move the same one as before
            FOR(k, 1, M) chmin(px[jn][k], px[jc][k] + abs(x - y) + pyd);
            // case 2: we move the other one
            if (py != -1) {
                FOR(k, 1, M) chmin(px[jn][py], px[jc][k] + abs(x - y) + abs(k - x));
                chmin(px[jn][py], px[jc][0] + abs(x - y));
            }
            py = y;
        }
        cout << *min_element(px[N & 1], px[N & 1] + M + 1) << endl;
    }
    return 0;
}

